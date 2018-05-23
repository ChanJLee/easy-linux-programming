#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::cout << "main pid: " << getpid() << std::endl;
    pid_t id = fork();
    switch(id) {
        case -1:
            std::cerr << "fork failed" << std::endl;
            break;
        case 0:
            std::cout << "I am child, pid: " << getpid() << " fork: " << id << std::endl;
            break;
        default:
            std::cout << "I am parent, pid: " << getpid() << " fork: " << id << std::endl;
            break;
    }

    return 0;
}