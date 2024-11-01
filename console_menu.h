#ifndef CONSOLE_MENU_H
#define CONSOLE_MENU_H

#include <map>
#include <functional>

using namespace std;

static void handleAddNewTextbook();
static void handleAddNewBookseller();
static void displayAllTextbooks();
static void displayAllBooksellers();

class ConsoleMenu {
private:
    map<string, function<void()>> menu_options;
    int menuOptionActive;

public:
    ConsoleMenu();
    void displayMenu();
    void handleUserInput();
    void setNewActiveMenuOption(int option_number);
    int getNewActiveMenuOption();
};

#endif // CONSOLE_MENU_H
