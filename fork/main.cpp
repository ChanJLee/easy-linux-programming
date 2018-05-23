#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    std::cout << "main pid: " << getpid() << std::endl;
    int exit_code = 0;
    pid_t id = fork();
    int i = 5;
    std::ostringstream os;

    switch (id)
    {
    case -1:
        std::cerr << "fork failed" << std::endl;
        break;
    case 0:
        exit_code = 37;
        os << "I am child, pid: " << getpid() << " fork: " << id;
        break;
    default:
        i = 2;
        os << "I am parent, pid: " << getpid() << " fork: " << id;
        break;
    }

    const std::string &msg = os.str();
    for (; i > 0; --i)
    {
        std::cout << msg << std::endl;
    }

    if (id)
    {
        std::cout << "wait for child" << std::endl;
        int mask;
        pid_t child = wait(&mask);
        std::cout << "catch child, pid: " << child << std::endl;
        if (WIFEXITED(mask))
        {
            std::cout << "child exit code is " << WEXITSTATUS(mask) << std::endl;
        } 
        else
        {
            std::cout << "child abort" << std::endl;
        }
    }

    return exit_code;
}
