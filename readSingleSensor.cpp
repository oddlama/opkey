#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdint>
#include <unistd.h>
#include <cmath>
#include <termios.h>
#include <fcntl.h>
#include <cstring>
#include <string>

#define TRANSACTION_BEGIN_CHAR '>'
#define TRANSACTION_BEGIN_COUNT 8

#define DEVICE       "/dev/ttyUSB0"
#define DATA_POINTS  (8 * 4096)

const char* outPath = ".";

std::string transaction_name(const char* sensorName, size_t transactionId) {
	std::string filename = outPath;
	filename += "/sensor_";
	filename += sensorName;
	filename += "_";
	filename += std::to_string(transactionId);
	return filename;
}

bool exists(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.data(), &buffer) == 0);
}

void die(const char* str) {
	dprintf(2, "%s\n", str);
	exit(1);
}

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

			char sensorName[4];
			read(fdUsb, sensorName, 4);

			size_t transactionId = 0;
			std::string filename;
			do {
				filename = transaction_name(sensorName, transactionId++);
			} while (exists(filename));
			int tFd = open(filename.data(), O_RDWR | O_CREAT, 0600);
			int64_t us;
			read(fdUsb, &us, sizeof(us));
			dprintf(1, "[host: readSingleSensor] got new data, time: %ldus\n", us);
			for (int i = 0; i < DATA_POINTS; ++i) {
				uint32_t val;
				int t = 0;
				while (t != 4) {
					int c = read(fdUsb, (char*)&val + t, sizeof(val) - t);
					if (c == -1)
						die("read() in transaction");
					t += c;
				}
				val =
					((((val & 0x000000ff) >>  0) - 'a') <<  0) |
					((((val & 0x0000ff00) >>  8) - 'a') <<  4) |
					((((val & 0x00ff0000) >> 16) - 'a') <<  8) |
					((((val & 0xff000000) >> 24) - 'a') << 12);
				dprintf(tFd, "%ld, %d, %f\n", (us * i / DATA_POINTS), val, sqrt(val));
			}
			close(tFd);
			++transactionId;
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
				++countSame;
			} else {
				countSame = 1;
			}

			if (countSame == TRANSACTION_BEGIN_COUNT && c == TRANSACTION_BEGIN_CHAR) {
				newTransaction = true;
			}
			lastC = c;
		}
	}
	return 0;
}
