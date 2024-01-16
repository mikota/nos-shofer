#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#include <string>

constexpr int device_num = 6;
constexpr int transmission_num = 10;
struct pollfd fds[device_num];

int main() {
    srand(time(NULL));
    for (int i = 0; i < device_num; i++) {
        std::string devname = "/dev/shofer" + std::to_string(i);
        fds[i].fd = open(devname.c_str(), O_WRONLY);
        if (fds[i].fd == -1) {
            std::cout << "Error opening file" << std::endl;
            return 1;
        }
        fds[i].events = POLLOUT;
    } 
    
    for (int i = 0; i < transmission_num; i++) {
        sleep(1);

        poll(fds, device_num, -1);

        for (int i = 0; i < device_num; i++) {
            if (fds[i].revents & POLLOUT) {
                char c = rand() % 26 + 'a';
                write(fds[i].fd, &c, 1);
                std::cout << "sent " << c << " to shofer " << i << std::endl;
            }
        }
    }

    for (int i = 0; i < device_num; i++) {
        close(fds[i].fd);
    }
}