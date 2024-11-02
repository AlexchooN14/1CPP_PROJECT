#ifndef CONSOLE_MENU_H
#define CONSOLE_MENU_H

// #include "utils.h"
// #include <iostream>
#include <map>
#include <string>
#include <functional>  // for the function template
// #include <conio.h> // Изисква се за използване на _getch() в Windows

using namespace std;

class ConsoleMenu {
private:
    // Map to keep console menu options and their corresponding function handlers
    map<string, function<void()>> menu_options = {};
    // Променлива в която запазваме индекса на избраната в момента опция от менюто
    int menuOptionActive;

public:
    ConsoleMenu();
    void setNewActiveMenuOption(int option_number);
    int getNewActiveMenuOption();
    
    void displayMenu();
    void handleUserInput();
};

string handleInput(function<bool(string&)> validator);
void handleAddNewTextbook();
void handleAddNewBookseller();
void displayAllTextbooks();
void displayAllBooksellers();

#endif //CONSOLE_MENU_H
