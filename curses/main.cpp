#include <iostream>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    WINDOW *win = initscr();

    move(0, 10);
    printw("%s", "hello world");
    refresh();

    move(1, 10);
    attron(A_BOLD);
    printw("%s", "hello world");
    attroff(A_BOLD);
    refresh();

    refresh();
    sleep(2);
    endwin();
    return 0;
}