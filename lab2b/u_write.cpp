#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

int main() {
    srand(time(NULL));
    int fd = open("/dev/shofer_out", O_WRONLY);
    if (fd == -1) {
        std::cout << "Error opening /dev/shofer_out" << std::endl;
        exit(1);
    }
    char c = 'a' + rand() % 26;
    write(fd, &c, 1);
    std::cout << "wrote " << c << " to /dev/shofer_out" << std::endl;
    close(fd);
    return 0;
}