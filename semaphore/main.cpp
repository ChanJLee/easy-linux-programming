#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>

char msg[1024] = {0};
sem_t sem;

void *thread_func(void *data);

int main(int argc, char *argv[])
{
    pthread_t t;
    std::cout << "init code: " << sem_init(&sem, 0, 1) << std::endl;

    const char echo[] = "hello world";
    std::cout << "write to sub thread, len " << sizeof(echo) << std::endl;
    memcpy(msg, echo, sizeof(echo));

    int code = pthread_create(&t, NULL, &thread_func, msg);
    if (code != 0)
    {
        std::cerr << "create thread failed" << std::endl;
        return -1;
    }

    sem_post(&sem);
    void *ret_data;
    code = pthread_join(t, &ret_data);
    if (code != 0)
    {
        std::cerr << "join failed" << std::endl;
        return -2;
    }

    std::cout << "result: " << (char *)ret_data << std::endl;
    sem_destroy(&sem);

    return 0;
}

void *thread_func(void *data)
{
    std::cout << "wait code: " << sem_wait(&sem) << std::endl;
    std::cout << "sub thread is running, receive msg: " << (char *)data << std::endl;
    const char *response = "WTF";
    memcpy(msg, response, sizeof(response));
    pthread_exit(msg);
}