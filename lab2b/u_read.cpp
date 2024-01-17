#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

int main() {
    srand(time(NULL));
    int fd = open("/dev/shofer_out", O_RDONLY);
    if (fd == -1) {
        std::cout << "Error opening /dev/shofer_in" << std::endl;
        exit(1);
    }
    char c = ' ';
    read(fd, &c, 1);
    std::cout << "read " << c << " from /dev/shofer_in" << std::endl;
    close(fd);
    return 0;
}