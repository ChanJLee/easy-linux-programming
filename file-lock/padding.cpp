#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int fd = open("padding.txt", O_CREAT | O_TRUNC | O_WRONLY, 666);
    if (fd < 0) 
    {
        std::cerr << "error" << std::endl;
        return -1;
    }

    std::cout << "fd " << fd << std::endl;

    char segment[27] = {0};
    for (int i = 0; i < 26; ++i)
    {
        segment[i] = 'a' + i;
    }

    for (int i = 0; i < 100; ++i)
    {
        std::cout << "write " << write(fd, segment, sizeof(segment)) << std::endl;
    }

    close(fd);
    return 0;
}