#include <iostream>
#include <termios.h>

int main(int argc, char* argv[])
{
    std::cout << "enter your password:" << std::endl;
    struct termios src, config;
    tcgetattr(fileno(stdin), &src);

    char password[100] = {0};
    memcpy(&config, &src, sizeof(struct termios));
    config.c_lflag &= ~ECHO;
    if (tcsetattr(fileno(stdin), TCSAFLUSH, &config) != 0) {
        std::cerr << "can not set termios" << std::endl;
        return -1;
    }

    fgets(password, 100, stdin);
    tcsetattr(fileno(stdin), TCSANOW, &src);
    std::cout << "your password: " << password << std::endl;
    return 0;
}