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
    //show_dialog_std();
    show_dialog_tty();
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
                break;
            }
            ++menu_item;
        }

        if (*menu_item == NULL) {
            std::cerr << "invalid argument " << o << std::endl;
        }

        char x = getchar();
        while (x != '\n') {
            x = getchar();
        }
    } while(o != 'q');
}

#include <cstdlib>

void show_dialog_tty()
{
    FILE* in = fopen("/dev/tty", "r");
    if (in == NULL) {
        std::cerr << "open tty failed" << std::endl;
        return;
    }

    FILE* out = fopen("/dev/tty", "w");
    if (out == NULL) {
        fclose(in);
        std::cerr << "open tty failed" << std::endl;
        return;
    }

    char o;
    do {
        const char** menu_item = menu;
        while(*menu_item) {
            fprintf(out, "%s\n", *menu_item);
            ++menu_item;
        }

        o = fgetc(in);
        menu_item = menu;
        while(*menu_item) {
            if (*menu_item[0] == o) {
                fprintf(out, "you select: %s\n", *menu_item);
                break;
            }
            ++menu_item;
        }

        if (*menu_item == NULL) {
            std::cerr << "invalid argument " << o << std::endl;
        }

        char x = fgetc(in);
        while (x != '\n') {
            x = fgetc(in);
        }
    } while(o != 'q');

    fclose(in);
    fclose(out);
}