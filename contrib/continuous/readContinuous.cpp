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

#define PARAMETER_TRANSFER_BEGIN_CHAR   '\004'
#define PARAMETER_TRANSFER_BEGIN_COUNT  8
#define PRE_RECORD_TAG_CHAR      '\005'
#define PRE_RECORD_TAG_COUNT     8
#define TRANSACTION_BEGIN_CHAR   '\027'
#define TRANSACTION_BEGIN_COUNT  8

#define CMD_PRE_RECORD   "./arecord.sh"
#define CMD_POST_RECORD   "./kill_arecord.sh"
//#define CMD_POST_RECEIVE "./post-receive.sh"

#define DEVICE       "/dev/ttyUSB0"


const char* outPath = ".";

struct CalibrationData {
	double min = 0.0;
	double max = 0.0;

	inline static constexpr const uint16_t maxSensorValue = 0xfff;

	double Apply(uint16_t rawSensorValue) {
		double s = static_cast<double>(rawSensorValue) / (maxSensorValue + 1);
		return (sqrt(s) - min) / (max - min);
	}
};

std::chrono::steady_clock::time_point overallBegin{};
struct {
	std::chrono::steady_clock::time_point recordBegin{};
	std::chrono::steady_clock::time_point recordEnd{};
	CalibrationData calibrationData{};
	uint64_t uniqueSessionId = 0;
	std::string sensorName{};
} meta;

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
			auto dataPoints = ReadDec<uint32_t>(fdUsb);
			auto us = std::chrono::duration_cast<std::chrono::microseconds>(meta.recordEnd - meta.recordBegin).count();
			auto usAtBegining = std::chrono::duration_cast<std::chrono::microseconds>(meta.recordBegin - overallBegin).count();

			dprintf(1, "[>] Receiving %u bytes for %s, elapsed time: %.3fms\n", dataPoints * 4, meta.sensorName.data(), us / 1000.0);
			std::string filename = next_transaction_name(meta.sensorName);
			int64_t runningDelta = 0;
			if (auto of = std::ofstream{filename}; of) {
				for (int i = 0; i < dataPoints; ++i) {
					auto delta = ReadDec<uint16_t>(fdUsb);
					runningDelta += delta;
					auto rawPos = ReadDec<uint16_t>(fdUsb);
					auto val = meta.calibrationData.Apply(rawPos);
					of  << runningDelta
						<< ","
						<< delta
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
				    << std::chrono::duration_cast<std::chrono::microseconds>(overallBegin.time_since_epoch()).count()
					<< "\n"
				    << std::chrono::duration_cast<std::chrono::microseconds>(meta.recordBegin.time_since_epoch()).count()
					<< "\n"
					<< std::chrono::duration_cast<std::chrono::microseconds>(meta.recordEnd.time_since_epoch()).count()
					<< "\n"
					<< runningDelta
					<< "\n"
					;
			} else {
				die("meta ofstream()");
			}

			dprintf(1, "[>] Data received.\n");
			//system((std::string(CMD_POST_RECEIVE) + " " + filename + " " + std::to_string(meta.uniqueSessionId)).data());
			++meta.uniqueSessionId;
			meta.recordBegin = std::chrono::steady_clock::now();
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
					system((std::string(CMD_POST_RECORD)).data());
					meta.recordEnd = ch::steady_clock::now();
					newTransaction = true;
				} else if (countSame == PRE_RECORD_TAG_COUNT && c == PRE_RECORD_TAG_CHAR) {
					meta.recordBegin = ch::steady_clock::now();
					system((std::string(CMD_PRE_RECORD) + " " + outPath + " " + std::to_string(meta.uniqueSessionId)).data());
				} else if (countSame == PARAMETER_TRANSFER_BEGIN_COUNT && c == PARAMETER_TRANSFER_BEGIN_CHAR) {
					auto sensorNameRaw = ReadDec<std::array<char, 4>>(fdUsb);
					for (auto& c : sensorNameRaw) {
						if (c == '#') {
							c = '+';
						}
					}

					size_t snLen = 0;
					for (; snLen < sensorNameRaw.size() && sensorNameRaw[snLen] != '\0'; ++snLen) { }
					meta.sensorName = std::string_view{sensorNameRaw.data(), snLen};
					meta.calibrationData = ReadDec<CalibrationData>(fdUsb);
					dprintf(1, "[>] Calibration data: min %f, max %f\n", meta.calibrationData.min, meta.calibrationData.max);
					overallBegin = ch::steady_clock::now();
					dprintf(1, "[>] META received.\n");
				}
			} else {
				countSame = 1;
			}

			lastC = c;
		}
	}
	return 0;
}
