#include <iostream>
#include <unistd.h>
#include <string>

int main(int argc, char *argv[])
{
    int fd[2] = {0};
    int code = pipe(fd);
    if (code == -1)
    {
        std::cerr << "open pipe failed" << std::endl;
        return -1;
    }

    pid_t id = fork();
    switch (id)
    {
    case -1:
        std::cerr << "fork failed" << std::endl;
        return -2;
    case 0:
        std::cout << "child";
        close(1);
        close(fd[1]);
        int len;
        char buf[17];
        while ((len = read(fd[0], buf, 16)) > 0)
        {
            buf[len] = 0;
            std::cout << "recv: " << buf << std::endl;
        }
        std::cout << "end";
        break;
    default:
        close(fd[0]);
        while (true)
        {
            std::cout << "input your message: ";
            std::string str;
            std::cin >> str;

            if (str == "exit")
            {
                close(fd[1]);
                break;
            }
            write(fd[1], str.c_str(), str.size());
        }
    
        close(fd[1]);
        break;
    }

    return 0;
}