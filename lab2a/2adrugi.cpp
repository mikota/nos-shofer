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
    retreat_on_sigint();
    open_fds(O_WRONLY);
    
    while(1) {
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
    retreat();
}