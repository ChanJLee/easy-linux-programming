#include <iostream>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{

    struct sockaddr_un servier_address;
    struct sockaddr_un client_address;

    unlink("fuck_bch");
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    servier_address.sun_family = AF_UNIX;
    strcpy(servier_address.sun_path, "fuck_bch");
    bind(fd, (const sockaddr *)&servier_address, sizeof(servier_address));
    listen(fd, 5);

    while(true) 
    {
        std::cout << "wait" << std::endl;
        socklen_t client_len = sizeof(client_address);
        int client_fd = accept(fd, (sockaddr *) &client_address, &client_len);

        char buf[256] = {0};
        ssize_t len;
        while((len = read(client_fd, buf, 255)) > 0)
        {
            std::cout << buf;
            memset(buf, 0, sizeof(buf));
        }
        close(client_fd);
    }

    return 0;
}