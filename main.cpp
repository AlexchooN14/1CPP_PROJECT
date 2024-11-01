#include "console_menu.h"
#include "data_management.h"

int main() {
    ConsoleMenu menu;

    while(true) {
        menu.displayMenu();
        menu.handleUserInput();
        writeNewDataToFile();
    }

    return 0;
}
