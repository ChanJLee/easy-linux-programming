#include <iostream>
#include <unistd.h>
#include <signal.h>

void handler(int sig) 
{
    std::cout << "recv sig " << sig << std::endl;
}

int main(int argc, char* argv[])
{
    struct sigaction action;
    
    action.sa_handler = &handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, NULL);

    for (int i = 0;; ++i)
    {
        sleep(1);
        std::cout << "sleep " << i << " s" << std::endl;
    }

    return 0;
}