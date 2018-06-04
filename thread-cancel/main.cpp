#include <pthread/pthread.h>
#include <iostream>
#include <unistd.h>

void* thread_func(void* data);

int sig = 0;

int main(int argc, char const *argv[])
{
    pthread_t t;
    pthread_attr_t attr;

    int code = pthread_attr_init(&attr);
    if (code != 0)
    {
        std::cerr << "init attr failed" << std::endl;
        return -1;
    }

    code = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (code != 0)
    {
        std::cerr << "set detached failed" << std::endl;
        return -2;
    }

    code = pthread_create(&t, &attr, thread_func, &sig);
    if (code != 0)
    {
        std::cerr << "create thread failed" << std::endl;
        return -3;
    }

    pthread_attr_destroy(&attr);
    std::cout << "shut down thread after 5s" << std::endl;
    sleep(5);
    code = pthread_cancel(t);
    if (code != 0)
    {
        std::cerr << "cancel thread failed" << std::endl;
        return -4;
    }

    return 0;
}

void* thread_func(void* data)
{
    int code = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (code != 0)
    {
        std::cerr << "set thread cancelable failed" << std::endl;
        pthread_exit(NULL); 
    }

    while(true)
    {
        sleep(1);
        std::cout << "WTF" << std::endl;
    }

    int* x = (int*) data;
    *x = 1;
    pthread_exit(data);
    return NULL;
}
