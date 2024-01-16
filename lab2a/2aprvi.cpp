#include <poll.h>
#include <fcntl.h>

constexpr int device_num = 6;

struct pollfd fds[device_num];

int main() {
    for (int i = 0; i < device_num; i++) {
        std::string devname = "/dev/shofer/" + std::to_string(i);
        fds[i].fd = open(devname.c_str(), O_RDONLY);
        fds[i].events = POLLIN;
    } 

    poll(fds, device_num, -1);
    
    for (int i = 0; i < device_num; i++) {
        if (fds[i].revents & POLLIN) {
            char buf[1024];
            read(fds[i].fd, buf, 1024);
            std::cout << buf << std::endl;
        }
    }

    for (int i = 0; i < device_num; i++) {
        close(fds[i]);
    }
}