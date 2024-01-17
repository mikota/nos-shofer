#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>

/* for ioctl */
#define SHOFER_IOCTL_TYPE	0x8A /* type, unused by https://www.kernel.org/doc/Documentation/ioctl/ioctl-number.txt */
#define SHOFER_IOCTL_NR		1 /* serial number */
#define SHOFER_IOCTL_COPY	1 /* command */

struct shofer_ioctl {
	unsigned int command;
	unsigned int count;
};


int main() {
    int fd = open("/dev/shofer_control", O_RDWR);
    if (fd == -1) {
        std::cout << "Error opening /dev/shofer_control" << std::endl;
        exit(1);
    }

    struct shofer_ioctl cmd;
    cmd.command = SHOFER_IOCTL_COPY;
    cmd.count = 1;
    ioctl(fd, SHOFER_IOCTL_TYPE, &cmd);

    close(fd);
    return 0;
}