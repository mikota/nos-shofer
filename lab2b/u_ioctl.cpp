#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include "config.h"



int main() {
    int fd = open("/dev/shofer_control", O_RDONLY);
    if (fd == -1) {
        std::cout << "Error opening /dev/shofer_control" << std::endl;
        exit(1);
    }

    struct shofer_ioctl cmd;
    unsigned long request;
    request = _IOC(_IOC_READ, SHOFER_IOCTL_TYPE, SHOFER_IOCTL_NR, sizeof(cmd));
    cmd.command = SHOFER_IOCTL_COPY;
    cmd.count = 1;
    
    int cnt = ioctl(fd, request, (unsigned long)&cmd);
    if (cnt == -1) {
        std::cout << "Error ioctl" << std::endl;
        close(fd);
        exit(1);
    }
    std::cout << "copied " << cnt << " bytes" << std::endl;
    close(fd);
    return 0;
}