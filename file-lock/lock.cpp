#include <fcntl.h>
#include <iostream>
#include "lock.h"

const char* lock_name = "tmp.lock";

int lock()
{
    int fd = open(lock_name, O_RDWR | O_CREAT | O_EXCL, 0444);
    if (fd == -1) {
        std::cerr << "error " << errno << std::endl;
    }
    return fd;
}