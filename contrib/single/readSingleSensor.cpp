#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdint>
#include <unistd.h>
#include <cmath>
#include <termios.h>
#include <fcntl.h>
#include <cstring>
#include <fstream>
#include <chrono>
#include <array>
#include <string>
#include <string_view>

#define PRE_RECORD_TAG_CHAR      '\005'
#define PRE_RECORD_TAG_COUNT     8
#define POST_RECORD_TAG_CHAR     '\004'
#define POST_RECORD_TAG_COUNT    8
#define TRANSACTION_BEGIN_CHAR   '\027'
#define TRANSACTION_BEGIN_COUNT  8

#define CMD_PRE_RECORD   "./pre_record.sh"
#define CMD_POST_RECEIVE "./post_receive.sh"

#define DEVICE       "/dev/ttyUSB0"

const char* outPath = ".";

struct {
	std::chrono::steady_clock::time_point recordBegin{};
	std::chrono::steady_clock::time_point recordEnd{};
	uint64_t reportedNanos = 0;
	bool valid = false;
	uint64_t uniqueSessionId = 0;
} meta;

struct CalibrationData {
	double min = 0.0;
	double max = 0.0;

	inline static constexpr const uint16_t maxSensorValue = 0xfff;

	double Apply(uint16_t rawSensorValue) {
		double s = static_cast<double>(rawSensorValue) / maxSensorValue;
		return (sqrt(s) - min) / (max - min);
	}
};

bool exists(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.data(), &buffer) == 0);
}

std::string next_transaction_name(std::string_view sensorName) {
	size_t transactionId = 0;
	std::string filename;
	do {
		filename = outPath;
		filename += "/sensor_";
		filename += sensorName;
		filename += "_";
		filename += std::to_string(transactionId);
		filename += ".raw";
		++transactionId;
	} while (exists(filename));
	return filename;
}

void die(const char* str) {
	dprintf(2, "%s\n", str);
	exit(1);
}

template<typename T>
inline T Read(int fd) {
	T t;
	size_t total = 0;
	while (total != sizeof(T)) {
		int c = read(fd, (char*)&t + total, sizeof(T) - total);
		if (c == -1) {
			die("read() in transaction");
		}
		total += c;
	}
	return t;
};

template<typename T>
inline T ReadDec(int fd) {
	T t;
	for (int i = 0; i < sizeof(T); ++i) {
		auto val = Read<uint16_t>(fd);
		reinterpret_cast<uint8_t*>(&t)[i] =
			((((val & 0x000000ff) >> 0) - 'a') << 0) |
			((((val & 0x0000ff00) >> 8) - 'a') << 4);
	}
	return t;
};

int main(int argc, char** argv) {
	if (argc != 2) {
		die("need out path");
	}
	outPath = argv[1];
	if (!exists(outPath)) {
		die("out path must exist");
	}
	int fdUsb = open(DEVICE, O_RDWR | O_NOCTTY);

	struct termios tty;
	struct termios tty_old;
	memset(&tty, 0, sizeof(tty));

	/* Error Handling */
	if ( tcgetattr ( fdUsb, &tty ) != 0 ) {
		die("tcgetattr()");
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B115200);
	cfsetispeed (&tty, (speed_t)B115200);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( fdUsb, TCIFLUSH );
	if ( tcsetattr ( fdUsb, TCSANOW, &tty ) != 0) {
		die("tcsetattr()");
	}

	char lastC = 0;
	int countSame = 1;
	bool newTransaction = false;
	while (true) {
		if (newTransaction) {
			newTransaction = false;

			auto sensorNameRaw = ReadDec<std::array<char, 4>>(fdUsb);
			for (auto& c : sensorNameRaw) {
				if (c == '#') {
					c = '+';
				}
			}

			size_t snLen = 0;
			for (; snLen < sensorNameRaw.size() && sensorNameRaw[snLen] != '\0'; ++snLen) { }
			auto sensorName = std::string_view{sensorNameRaw.data(), snLen};

			auto calibrationData = ReadDec<CalibrationData>(fdUsb);
			auto us = ReadDec<int64_t>(fdUsb);
			meta.reportedNanos = static_cast<uint64_t>(us) * 1000;

			auto dataPoints = ReadDec<uint32_t>(fdUsb);

			dprintf(1, "[>] Receiving %u bytes for %.*s, elapsed time: %.3fms\n", dataPoints, (int)snLen, sensorName.data(), us / 1000.0);
			dprintf(1, "[>] Calibration data: min %f, max %f\n", calibrationData.min, calibrationData.max);
			std::string filename = next_transaction_name(sensorName);
			if (auto of = std::ofstream{filename}; of) {
				for (int i = 0; i < dataPoints; ++i) {
					auto val = calibrationData.Apply(ReadDec<uint16_t>(fdUsb));
					of  << (us * i / dataPoints)
						<< ","
						<< val
						<< "\n"
						;
				}
			} else {
				die("file ofstream()");
			}

			if (auto of = std::ofstream{filename + ".meta"}; of) {
				of  << meta.uniqueSessionId
					<< "\n"
				    << std::chrono::duration_cast<std::chrono::nanoseconds>(meta.recordBegin.time_since_epoch()).count()
					<< "\n"
					<< std::chrono::duration_cast<std::chrono::nanoseconds>(meta.recordEnd.time_since_epoch()).count()
					<< "\n"
					<< meta.reportedNanos
					<< "\n"
					;
			} else {
				die("meta ofstream()");
			}

			dprintf(1, "[>] Data received.\n");
			system((std::string(CMD_POST_RECEIVE) + " " + filename + " " + std::to_string(meta.uniqueSessionId)).data());
			meta.valid = false;
			++meta.uniqueSessionId;
		} else {
			char c;
			int r = read(fdUsb, &c, 1);
			if (r == -1) {
				die("read() in idle");
			}
			if (r != 1) {
				continue;
			}
			write(1, &c, 1);

			if (c == lastC) {
				namespace ch = std::chrono;
				++countSame;
				if (countSame == TRANSACTION_BEGIN_COUNT && c == TRANSACTION_BEGIN_CHAR) {
					if (not meta.valid) {
						die("missing pre record tag");
					}
					newTransaction = true;
				} else if (countSame == PRE_RECORD_TAG_COUNT && c == PRE_RECORD_TAG_CHAR) {
					meta.valid = true;
					meta.recordBegin = ch::steady_clock::now();
					system((std::string(CMD_PRE_RECORD) + " " + outPath + " " + std::to_string(meta.uniqueSessionId)).data());
				} else if (countSame == POST_RECORD_TAG_COUNT && c == POST_RECORD_TAG_CHAR) {
					meta.recordEnd = ch::steady_clock::now();
				}
			} else {
				countSame = 1;
			}

			lastC = c;
		}
	}
	return 0;
}
