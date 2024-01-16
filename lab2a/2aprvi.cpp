#include "2a.h"
#include <string>

int main() {
    retreat_on_sigint();
    open_fds(O_RDONLY);
    while(1) {
        poll(fds, device_num, -1);
        
        for (int i = 0; i < device_num; i++) {
            if (fds[i].revents & POLLIN) {
                char c;
                read(fds[i].fd, &c, 1);
                std::cout << "read " << c << " from shofer " << i << std::endl;
            }
        }
    }
    retreat();
}