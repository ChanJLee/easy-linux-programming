#include <iostream>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

struct Message {
    char msg[512];
};

int msg_id;

void child_process();

void main_process();

int main(int argc, char* argv[])
{
    msg_id = msgget(1234, 0666 | IPC_CREAT);
    if (msg_id == -1)
    {
        std::cerr << "create msg que failed" << std::endl;
        return -1;
    }

    pid_t id = fork();
    switch(id)
    {
        case -1:
            std::cerr << "fork failed" << std::endl;
            return -2;
        case 0:
            child_process();
            break;
        default:
            main_process();
            break;
    }

    return 0;
}

void child_process()
{
    std::cout << "child " << getpid() << std::endl;
    char content[256] = "hello world\0";
    Message msg;
    memcpy(msg.msg, content, sizeof(content));

    if (msgsnd(msg_id, &msg, sizeof(Message), 0) == -1)
    {
        std::cerr << "send failed" << std::endl;
    }
}

void main_process()
{
    std::cout << "parent " << getpid() << std::endl;
    Message msg;
    long session = 0;
    while(true) 
    {
        if (msgrcv(msg_id, &msg, sizeof(Message), session, 0) == -1)
        {
            std::cerr << "rcv msg failed" << std::endl;
            return;
        }

        std::cout << msg.msg << std::endl;
        break;
    }

    std::cout << "try to release" << std::endl;
    if (msgctl(msg_id, IPC_RMID, 0) == -1)
    {
        std::cerr << "destroy msg failed" << std::endl;
    }
}