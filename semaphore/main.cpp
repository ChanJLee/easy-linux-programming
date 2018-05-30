#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>

char msg[1024] = {0};
sem_t* sem;

void *thread_func(void *data);

int main(int argc, char *argv[])
{
    pthread_t t;
    sem = sem_open("sem", O_CREAT|O_EXCL, S_IRWXU, 0);

    const char echo[] = "hello world";
    std::cout << "write to sub thread, len " << sizeof(echo) << std::endl;
    memcpy(msg, echo, sizeof(echo));

    int code = pthread_create(&t, NULL, &thread_func, msg);
    if (code != 0)
    {
        std::cerr << "create thread failed" << std::endl;
        return -1;
    }

    sem_post(sem);
    char *ret_data;
    code = pthread_join(t, (void**) &ret_data);
    if (code != 0)
    {
        std::cerr << "join failed" << std::endl;
        return -2;
    }

    std::cout << "result: " << ret_data << std::endl;
    sem_close(sem);

    return 0;
}

void *thread_func(void *data)
{
    std::cout << "wait code: " << sem_wait(sem) << std::endl;
    std::cout << "sub thread is running, receive msg: " << (char *)data << std::endl;
    pthread_exit(data);
}