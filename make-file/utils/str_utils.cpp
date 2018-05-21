#include "str_utils.h"
#include <string.h>
#include "utils.h"

int len(const char* str)
{
    if (str == nullptr)
    {
        echo("str is null");
        return 0;
    }

    return strlen(str);
}