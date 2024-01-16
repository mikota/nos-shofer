#include "2a.h"
#include <string>
#include <vector>

int main() {
    srand(time(NULL));
    retreat_on_sigint();
    open_fds(O_WRONLY);
    
    while(1) {
        sleep(1);

        poll(fds, device_num, -1);

        std::vector<int> ready_fds;
        std::cout << "shofers ready: ";
        for (int i = 0; i < device_num; i++) {
            if (fds[i].revents & POLLOUT) {
                ready_fds.push_back(i);
                std::cout << i << " ";
            }
        } 
        int fd = ready_fds[rand() % ready_fds.size()];
        char c = 'a' + rand() % 26;
        write(fds[fd].fd, &c, 1);
        std::cout << "\t->wrote " << c << " to shofer " << fd << std::endl;
        std::cout << std::flush;
    }
    retreat();
}