#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main_process(pid_t child);

int child_process();

void handler(int sig);

int main(int argc, char* argv[])
{
    pid_t id = fork();
    switch(id) {
        case -1:
            std::cerr << "fork failed" << std::endl;
            return -1;
        case 0:
            return child_process();
        default:
            return main_process(id);
    }

    return 0;
}

int main_process(pid_t child)
{

    std::cout << "boom after 5s" << std::endl;
    sleep(5);
    kill(child, SIGINT);
    return 0;
}


int child_process() {
    signal(SIGINT, handler);
    while (true) {
        std::cout << "wait sig" << std::endl;
        sleep(1);
    }
    return 0;
}

void handler(int sig) 
{
    std::cout << "recv sig " << sig << std::endl;
    exit(sig);
}