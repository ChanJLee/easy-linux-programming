#include "utils/utils.h"

int main(int argc, char* argv[])
{
    #ifdef DEBUG
    echo("debug");
    #else
    echo("release");
    #endif
    return 0;
}