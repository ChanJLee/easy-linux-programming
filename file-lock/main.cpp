#include <iostream>
#include "lock.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::cout << "A" << std::endl;
    int mutex = -1;
    while((mutex = lock()) != -1)
    {
        std::cout << "A wait for lock" << std::endl;
        sleep(1);
    }

    std::cout << "A get lock" << std::endl;
    sleep(5);
    std::cout << "A finished" << std::endl;
    unlock(mutex);

    return 0;
}