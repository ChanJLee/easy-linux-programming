#include <iostream>

int main(int argc, char *argv[])
{
    const char *linux_pro_env = getenv("linux_pro_env");
    if (strlen(linux_pro_env))
    {
        std::cout << "linux pro env" << linux_pro_env << std::endl;
    }

    const char* env = "linux_pro_env=hello_world";
    char* env_dy = (char*) malloc(strlen(env) + 1);
    memset(env_dy, 0, strlen(env) + 1);
    memcpy(env_dy, env, strlen(env));

    if (putenv(env_dy))
    {
        std::cerr << "put linux_pro_env failed" << std::endl;
        return -2;
    }

    return 0;
}