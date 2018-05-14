#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const char *linux_pro_env = getenv("linux_pro_env");
    if (linux_pro_env && strlen(linux_pro_env))
    {
        std::cout << "linux pro env" << linux_pro_env << std::endl;
    }

    const char* env = "linux_pro_env=hello_world";
    const size_t len = strlen(env);

    // free on exit
    char* env_dy = (char*) malloc(len + 1);
    memset(env_dy, 0, len + 1);
    memcpy(env_dy, env, len);

    if (putenv(env_dy))
    {
        std::cerr << "put linux_pro_env failed" << std::endl;
        return -2;
    }

    std::cout << getenv("linux_pro_env") << std::endl;

    return 0;
}