#include <iostream>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

    struct sockaddr_in servier_address;
    struct sockaddr_in client_address;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        std::cerr << "open socket failed" << std::endl;
        return -1;
    }
    std::cout << "open socket at: " << fd << std::endl; 
    servier_address.sin_family = AF_INET;
    servier_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    servier_address.sin_port = 8765;

    if (bind(fd, (struct sockaddr *)&servier_address, sizeof(servier_address)) < 0)
    {   
        std::cerr << "bind failed: " << errno << std::endl;
        return -2;
    }

    if (listen(fd, 5) < 0) 
    {
        std::cerr << "listen failed" << std::endl;
        return -3;
    }

    while(true) 
    {
        std::cout << "wait" << std::endl;
        socklen_t client_len = sizeof(client_address);
        int client_fd = accept(fd, (sockaddr *) &client_address, &client_len);
        std::cout << "accept" << std::endl;
        
        char buf[256] = {0};
        ssize_t len;
        while((len = read(client_fd, buf, 255)) > 0)
        {
            std::cout << buf;
            memset(buf, 0, sizeof(buf));
        }
        close(client_fd);
    }

    std::cout << "end" << std::endl;
    return 0;
}