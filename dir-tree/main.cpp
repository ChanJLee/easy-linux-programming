#include <iostream>
#include <cstdlib>

#include <unistd.h>

void print_dir(const char *dir, int depth);

void print_depth(int depth, const char* place_holder);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "invalid arguments" << std::endl;
        return -1;
    }

    print_dir(argv[1], 0);
    return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <sstream>

const char* dir_place_holder = "    ";
const char* file_place_holder = "     ";

void print_dir(const char *dir, int depth)
{
    print_depth(depth, dir_place_holder);
    std::cout << dir << std::endl;
    DIR *handler = opendir(dir);
    if (handler == NULL)
    {
        // can not open dir
        return;
    }

    dirent *ent = NULL;
    struct stat buff = {0};
    std::vector<const char *> vec;
    while ((ent = readdir(handler)))
    {
        lstat(ent->d_name, &buff);
        if (S_ISDIR(buff.st_mode) &&
            strcmp(".", ent->d_name) != 0 &&
            strcmp("..", ent->d_name) != 0 &&
            strcmp(".DS_Store", ent->d_name) != 0)
        {
            vec.push_back(ent->d_name);
        }
        else
        {
            print_depth(depth, file_place_holder);
            std::cout << ent->d_name << std::endl;
        }
    }

    closedir(handler);

    std::for_each(vec.begin(), vec.end(), [=](const char *file) -> void {
        std::ostringstream ss;
        ss << dir << "/" << file;
        print_dir(ss.str().c_str(), depth + 1);
    });
}

void print_depth(int depth, const char* place_holder)
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << place_holder;
    }
}