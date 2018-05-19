#include <fcntl.h>
#include "lock.h"
#include <unistd.h>

const char* lock_name = "tmp.lock";

int lock()
{
    // normal
    int fd = open(lock_name, O_RDWR | O_CREAT | O_EXCL, 0444);
    return fd;
}

void unlock(int fd)
{
    close(fd);
    unlink(lock_name);
}

int lock_p()
{
    return 0;
}

void unlock_p(int fd)
{
    
}