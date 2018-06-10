#include <iostream>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>

int init();

int destroy();

int sem_p();

int sem_v();

int sem;
int mem;

int main_process(int argc);

int child_process(int argc);

int main(int argc, char *argv[])
{
    mem = shmget(6543, sizeof(int), 0666 | IPC_CREAT);
    if (mem == -1)
    {
        std::cerr << "open share mem failed" << std::endl;
        return -1;
    }

    pid_t id = fork();
    switch(id)
    {
        case -1:
            std::cerr << "fork failed" << std::endl;
        case 0:
            child_process(2);
            break;
        default:
            main_process(1);
            break;
    }

    return 0;
}

int sem_p()
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1; /* P() */
    buf.sem_flg = SEM_UNDO;
    return semop(sem, &buf, 1) == -1 ? -1 : 0;
}

int sem_v()
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1; /* V() */
    buf.sem_flg = SEM_UNDO;
    return semop(sem, &buf, 1) == -1 ? -1 : 0;
}

int init()
{
    sem = semget(54321, 1, 0666 | IPC_CREAT);
    union semun sem_union;
    sem_union.val = 1;
    return semctl(sem, 0, SETVAL, sem_union) == -1 ? -1 : 0;
}

int destroy()
{
    union semun sem_union;
    return semctl(sem, 0, IPC_RMID, sem_union) == -1 ? -1 : 0;
}

int main_process(int argc)
{
    char ch = argc == 2 ? 'X' : 'O';
    int* count_p = (int*) shmat(mem, 0, 0);
    if (count_p == (int*) -1)
    {
        return -5;
    }

    if (init())
    {
        std::cerr << "init failed" << std::endl;
        return -1;
    }

    int result = 0;
    for (int i = 6; i <= 10; ++i)
    {
        if (sem_p())
        {
             std::cerr << "p failed" << std::endl;
            return -2;
        }

        result = *count_p + i;
        *count_p = result;
        int fuck = result;
        std::cout << "|" << fuck;
        std::cout.flush();    

        if (sem_v())
        {
             std::cerr << "v failed" << std::endl;
            return -3;
        }
    }

    if (shmdt(count_p) == -1)
    {
        std::cerr << "detach failed" << std::endl;
        return -6;
    }

    std::cout << "main end" << std::endl;
    if (result== 55)
    {
        std::cout << "destroy mem" << std::endl;
        if (shmctl(mem, IPC_RMID, 0) == -1) {
            std::cerr << "destroy mem failed" << std::endl;
            return -7;
        }
    }

    if (destroy())
    {
        std::cerr << "release failed" << std::endl;
        return -4;
    }

    return 0;
}

int child_process(int argc)
{
    char ch = argc == 2 ? 'X' : 'O';
    int* count_p = (int*) shmat(mem, 0, 0);
    if (count_p == (int*) -1)
    {
        return -5;
    }

    if (init())
    {
        std::cerr << "init failed" << std::endl;
        return -1;
    }

    int result = 0;
    for (int i = 1; i <= 5; ++i)
    {
        if (sem_p())
        {
             std::cerr << "p failed" << std::endl;
            return -2;
        }

        result = *count_p + i;
        *count_p = result;
        int fuck = result;
        std::cout << "|" << fuck;
        std::cout.flush();    

        if (sem_v())
        {
             std::cerr << "v failed" << std::endl;
            return -3;
        }
    }

    if (shmdt(count_p) == -1)
    {
        std::cerr << "detach failed" << std::endl;
        return -6;
    }

    std::cout << "child end" << std::endl;
    if (result == 55)
    {
        std::cout << "destroy mem" << std::endl;
        if (shmctl(mem, IPC_RMID, 0) == -1) {
            std::cerr << "destroy mem failed" << std::endl;
            return -7;
        }
    }

    if (destroy())
    {
        std::cerr << "release failed" << std::endl;
        return -4;
    }

    return 0;
}