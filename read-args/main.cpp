#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, ":lf:")) != -1)
    {
        switch (opt)
        {
        case ':':
            std::cout << "need argument" << std::endl;
            break;
        case '?':
            std::cout << "unkown argument: " << optopt << std::endl;
            break;
        case 'f':
            std::cout << "f option value: " << optarg << std::endl;
            break;
        case 'l':
            std::cout << "enable l" << std::endl;
            break;
        }
    }

    std::cout << "optind value: " << optind << std::endl;
    for (; optind < argc; ++optind)
    {
        std::cout << "index: " << optind << " argument: " << argv[optind] << std::endl;
    }
    return 0;
}