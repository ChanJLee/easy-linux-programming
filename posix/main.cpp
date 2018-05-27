#include <iostream>
#include <unistd.h>
#include <pthread.h>

char message[] = "hello world";
char exit_msg[] = "thread exit";

void* thread_func(void* arg);

int main(int argc, char* argv[])
{

    std::cout << "message is " << message << std::endl;

    pthread_t t;
    int code = pthread_create(&t, NULL, thread_func, message);
    if (code != 0)
    {
        std::cerr << "create thread failed" << std::endl;
        return -1;
    }

    void* thread_result;
    code = pthread_join(t, &thread_result);
    if (code != 0)
    {
        std::cerr << "join thread failed" << std::endl;
        return -2;
    }

    std::cout << "message is " << message << std::endl;
    std::cout << "exit mssage is " << (char*) thread_result << std::endl;

    return 0;
}

void* thread_func(void* arg)
{
    std::cout << "thread is run, arg is " << (char*) arg << std::endl;
    sleep(3);
    strcpy(message, "HELLO WORLD");
    pthread_exit(exit_msg);
}