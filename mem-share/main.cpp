#include <iostream>
#include <unistd.h>
#include <sys/sem.h>

int init();

int destroy();

int sem_p();

int sem_v();

int sem;

int main(int argc, char *argv[])
{

    char ch = argc == 2 ? 'X' : 'O';

    if (init())
    {
        std::cerr << "init failed" << std::endl;
        return -1;
    }

    for (int i = 1; i < 10; ++i)
    {
        if (sem_p())
        {
             std::cerr << "p failed" << std::endl;
            return -2;
        }

        sleep(2);
        std::cout << ch;
        std::cout.flush();    

        if (sem_v())
        {
             std::cerr << "v failed" << std::endl;
            return -3;
        }
    }

    if (destroy())
    {
        std::cerr << "release failed" << std::endl;
        return -4;
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
    sem = semget(1234, 1, 0666 | IPC_CREAT);
    union semun sem_union;
    sem_union.val = 1;
    return semctl(sem, 0, SETVAL, sem_union) == -1 ? -1 : 0;
}

int destroy()
{
    union semun sem_union;
    return semctl(sem, 0, IPC_RMID, sem_union) == -1 ? -1 : 0;
}