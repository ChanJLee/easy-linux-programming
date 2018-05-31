#include <iostream>
#include <pthread/pthread.h>

void *thread_func(void *arg);

int pool[10] = {0};

pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    std::cout << "mutex init: "
              << pthread_mutex_init(&mutex, NULL)
              << std::endl
              << "input number: ";

    pthread_t t;
    pthread_create(&t, NULL, thread_func, pool);

    pthread_mutex_lock(&mutex);
    int x;
    std::cin >> x;
    pthread_mutex_unlock(&mutex);

    int* result;
    pthread_join(t, (void **)&result);

    std::cout << "result " << result[0] << " " << pool[0] << std::endl;

    return 0;
}

void *thread_func(void *arg)
{
    pthread_mutex_lock(&mutex);
    int *arr = (int *)arg;
    arr[0] = 10;
    pthread_mutex_unlock(&mutex);
    std::cout << "thread exit" << std::endl;
    pthread_exit(arg);
}