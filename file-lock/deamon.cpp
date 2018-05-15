#include <iostream>
#include "lock.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::cout << "B" << std::endl;
    int mutex = -1;
    while((mutex = lock()) != -1)
    {
        std::cout << "B wait for lock" << std::endl;
        sleep(1);
    }

    std::cout << "B get lock" << std::endl;
    sleep(5);
    std::cout << "B finished" << std::endl;
    close(mutex);
    unlink(lock_name);
    return 0;
}