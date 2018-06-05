#include <iostream>
#include "c.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (access(FIFO_NAME, F_OK) == -1)
    {
        int code = mkfifo(FIFO_NAME, 0777);
        if (code != 0) 
        {
            std::cerr << "make fifo failed" << std::endl;
            return -1;
        }
    }

    std::cout << "start writer" << std::endl;
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd != -1)
    {
        const char msg[] = "hello world!";
        write(fd, msg, sizeof(msg));
        close(fd);
    }

    std::cout << "writer end" << std::endl;

    return 0;
}