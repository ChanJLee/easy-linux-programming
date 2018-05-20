#include <iostream>

int main(int argc, char* argv[])
{
    #ifdef DEBUG
    std::cout << "debug" << std::endl;
    #else
    std::cout << "release" << std::endl;
    #endif
    return 0;
}