#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

const int segment_size = 20;

void lock(int fd, struct flock *lock, int start, int len, int action);

int main(int argc, char *argv[])
{
    int fd = open("padding.txt", O_RDWR | O_CREAT);
    if (fd < 0)
    {
        std::cerr << "deamon open padding failed" << std::endl;
        return -1;
    }

    int start = 20;
    struct flock mutex;
    lock(fd, &mutex, 20, segment_size, F_RDLCK);
    sleep(10);
    close(fd);
    return 0;
}

void lock(int fd, struct flock *lock, int start, int len, int action)
{
    lock->l_len = len;
    lock->l_pid = -1;
    lock->l_start = start;
    lock->l_whence = SEEK_SET;
    lock->l_type = action;

    std::cout << "deamon try to lock, start "
              << start
              << " end "
              << start + len
              << " type " << action
              << std::endl;

    int res = fcntl(fd, F_SETLK, lock);
    std::cout << "deamon fcntl result " << res << std::endl;
    if (res == -1)
    {
        std::cerr << "deamon get lock failed" << std::endl;
        close(fd);
        return;
    }

    if (lock->l_pid != -1)
    {
        std::cout << "deamon lock failed" << std::endl;
    }
    else
    {
        std::cout << "deamon lock success"
                  << " start " << lock->l_start
                  << " end " << lock->l_len + lock->l_start
                  << " pid " << lock->l_pid
                  << " type " << lock->l_type
                  << " whence " << lock->l_whence << std::endl;
    }
}