#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#include <string>


constexpr int device_num = 6;

struct pollfd fds[device_num];

int main() {
    for (int i = 0; i < device_num; i++) {
        std::string devname = "/dev/shofer/" + std::to_string(i);
        fds[i].fd = open(devname.c_str(), O_RDONLY);
        if (fds[i].fd == -1) {
            std::cout << "Error opening file" << std::endl;
            return 1;
        }
        fds[i].events = POLLIN;
    } 

    poll(fds, device_num, -1);
    
    for (int i = 0; i < device_num; i++) {
        if (fds[i].revents & POLLIN) {
            char c;
            read(fds[i].fd, &c, 1);
            std::cout << "shofer " << i << " sent " << c << std::endl;
        }
    }

    for (int i = 0; i < device_num; i++) {
        close(fds[i].fd);
    }
}