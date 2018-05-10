#include <iostream>
#include <curses.h>

int main(int argc, char* argv[])
{
    initscr();
    move(10, 10);
    printw("%s", "hello world");
    refresh();
    return 0;
}