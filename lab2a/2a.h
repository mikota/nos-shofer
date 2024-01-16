#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>

constexpr int device_num = 6;
struct pollfd fds[device_num];

void retreat() {
    for (int i = 0; i < device_num; i++) {
        close(fds[i].fd);
    }
    std::cout << "retreat" << std::endl;
    exit(0);
}

void retreat_on_sigint() {
    sigset(SIGINT, retreat);
}

int open_fds(int flags) {
    for (int i = 0; i < device_num; i++) {
        std::string devname = "/dev/shofer" + std::to_string(i);
        fds[i].fd = open(devname.c_str(), flags);
        if (fds[i].fd == -1) {
            std::cout << "Error opening " << devname << std::endl;
            retreat();
        }
        fds[i].events = flags == O_WRONLY ? POLLOUT : POLLIN;
    } 
}