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

    std::cout << "start reader" << std::endl;
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd != -1)
    {
        close(fd);
    }

    std::cout << "reader end" << std::endl;
    return 0;
}