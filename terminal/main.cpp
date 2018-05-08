#include <iostream>

void show_dialog_std();

void show_dialog_tty();

const char* menu[] = {
    "h - help",
    "o - ok",
    "q - quit",
    NULL
};

#include <unistd.h>
int main(int argc, char* argv[])
{
    // true is tty
    // fale is redirect
    std::cout << "is terminal: " << isatty(fileno(stdout)) << std::endl;
    show_dialog_std();
    return 0;
}

void show_dialog_std()
{
    char o;
    do {
        const char** menu_item = menu;
        while(*menu_item) {
            std::cout << *menu_item << std::endl;
            ++menu_item;
        }

        o = getchar();
        menu_item = menu;
        while(*menu_item) {
            if (*menu_item[0] == o) {
                std::cout << "you select: " << *menu_item << std::endl;
            }
            ++menu_item;
        }

        if (menu_item == NULL) {
            std::cerr << "invalid argument " << o << std::endl;
        }

        char x = getchar();
        while (x != '\n') {
            x = getchar();
        }
    } while(o != 'q');
}

void show_dialog_tty()
{
    
}