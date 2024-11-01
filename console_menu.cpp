#include "console_menu.h"
#include <iostream>
#include <conio.h> // For getch
#include "textbook.h"
#include "bookseller.h"
#include "utilities.h"

using namespace std;


// TODO: проверка на входните данни
static void handleAddNewTextbook() {
    string input;
    Textbook tb;
    tm release_date, date_mon_accepted;

    cout << "Please enter following parameters for new Textbook:" << endl;
    cout << "Textbook heading:" << endl;
    getline(cin, input);
    tb.setHeading(input);
    cout << "Textbook price:" << endl;
    getline(cin, input);
    tb.setPrice(stoi(input));
    cout << "Textbook Authors Count:" << endl;
    getline(cin, input);
    for (int i = 0; i < stoi(input); i++) {
        string author;
        cout << "Textbook Author " << i << " name:" << endl;
        getline(cin, author);
        tb.addAuthorToAuthors(author);
    }
    cout << "Textbook edition:" << endl;
    getline(cin, input);
    tb.setEdition(stoi(input));

    cout << "Textbook ISBN number:" << endl;
    getline(cin, input);
    tb.setIsbnNumber(input);

    cout << "Textbook Print Run:" << endl;
    getline(cin, input);
    tb.setPrintRun(stoi(input));

    cout << "Textbook release date (Year-Month-Date):" << endl;
    getline(cin, input);
    // Convert string to tm struct
    istringstream ss(input);
    ss >> get_time(&release_date, "%Y-%m-%d");
    tb.setReleaseDate(release_date);

    cout << "Is Textbook Accepted by MON (True/False):" << endl;
    getline(cin, input);
    bool mon_accepted = stringToBool(input);
    tb.setIsMonAccepted(stringToBool(input));

    if (mon_accepted) {
        cout << "Textbook MON acception date (Year-Month-Date):" << endl;
        getline(cin, input);
        // Convert string to tm struct
        istringstream ss(input);
        ss >> get_time(&date_mon_accepted, "%Y-%m-%d");
        tb.setDateMonAccepted(date_mon_accepted);
    }
    
    all_textbooks.push_back(tb);
    new_textbook_added = true;
}

static void handleAddNewBookseller() {
    string name, address, phone_number;
    cout << "Please enter name, address and phone number for the new bookseller:" << endl;
    cout << "Bookseller name:" << endl;
    getline(cin, name);
    cout << "Bookseller address:" << endl;
    getline(cin, address);
    cout << "Bookseller phone number:" << endl;
    getline(cin, phone_number);

    Bookseller bs(name, address, phone_number);
    all_booksellers.push_back(bs);
    new_bookseller_added = true;
}

static void displayAllTextbooks() {
    cout << "\\/=== All Textbooks ===\\/" << endl;
    for (const Textbook& textbook : all_textbooks) {
        cout << textbook << endl;
        cout << endl;
    }
    system("pause");
}

static void displayAllBooksellers() {
    cout << "\\/=== All Booksellers ===\\/" << endl;
    for (const Bookseller& bookseller : all_booksellers) {
        cout << bookseller << endl;
        cout << endl;
    }
    system("pause");
}

static void writeNewDataToFile() {
    if (!new_bookseller_added && !new_textbook_added) {
        return;
    }
    // make them false
    // write them


}


ConsoleMenu::ConsoleMenu () {
    this->menu_options = {
        {"Add a new Textbook", handleAddNewTextbook},
        {"Add a new Book Seller", handleAddNewBookseller},
        {"Display all Textbooks", displayAllTextbooks},
        {"Display all Book Sellers", displayAllBooksellers},
    };
    setNewActiveMenuOption(0);  // By default the first option of the menu is active
}

void ConsoleMenu::displayMenu() {
    system("cls");
    int index = 0;
    if (new_bookseller_added || new_textbook_added) 
        cout << "New data added successfully" << endl;
    for (auto const& menu_option_pair : this->menu_options) {
        cout << (this->menuOptionActive == index ? "> " : "  ") << menu_option_pair.first << endl;
        index++;
    }
}

void ConsoleMenu::handleUserInput() {
    char key = getch();

    // Define iterator here to avoid jumping into variable's uninitilized scope which causes error
    auto it = this->menu_options.begin();

    switch (key) {
        case KEYBOARD_BUTTON_UP:
            this->menuOptionActive = (this->menuOptionActive == 0) ? (this->menu_options.size() - 1) : (this->menuOptionActive - 1);
            break;
        case KEYBOARD_BUTTON_DOWN:
            this->menuOptionActive = (this->menuOptionActive + 1) % (this->menu_options.size());
            break;
        case KEYBOARD_BUTTON_ENTER:
            // Get the active option instance from the menu map and call its corresponding callout function
            advance(it, this->menuOptionActive); // Move the iterator to the desired index
            it->second();
            break;
        case KEYBOARD_CTRL_C:
        case KEYBOARD_ESC:
            exit(1);
        default:
            break;
    }
}

void ConsoleMenu::setNewActiveMenuOption(int option_number) {
    this->menuOptionActive = option_number;
}

int ConsoleMenu::getNewActiveMenuOption() {
    return this->menuOptionActive;
}
