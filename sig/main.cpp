#include <iostream>
#include <unistd.h>
#include <signal.h>

void handler(int sig) 
{
    std::cout << "WTF, sig is " << sig << std::endl;
    signal(SIGINT, SIG_DFL);
}

int main(int argc, char* argv[])
{
    printf("handler address 0x%lx\n", (long) &handler);
    long address = (long) signal(SIGINT, &handler);
    printf("signal return address 0x%lx\n", address);

    while(true) {
        std::cout << "running" << std::endl;
        sleep(1);
    }

    return 0;
}