#include "console_menu.h"
#include "main.h"
#include "order.h"
#include <map>
#include <functional>  // for the function template
#include <conio.h> // Изисква се за използване на _getch() в Windows

using namespace std;


ConsoleMenu::ConsoleMenu () {
    this->menu_options = {
        {"Add a new Textbook", handleAddNewTextbook},
        {"Add a new Book Seller", handleAddNewBookseller},
        {"Display all Textbooks", displayAllTextbooks},
        {"Display all Book Sellers", displayAllBooksellers},
        {"Create an Order", handleCreateNewOrder},
    };
    // Задаваме първото меню като избрано по подразбиране
    setNewActiveMenuOption(0);
}

void ConsoleMenu::setNewActiveMenuOption(int option_number) {
    this->menuOptionActive = option_number;
}

int ConsoleMenu::getNewActiveMenuOption() {
    return this->menuOptionActive;
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

string handleInput(function<bool(string&)> validator) {
    string input;

    while (true) {
        getline(cin, input);

        if (validator(input)) {
            return input;
        }

        cout << "Invalid input. Try again!" << endl;
    }

    return NULL;
}

void handleAddNewTextbook() {
    string input;
    Textbook tb;
    tm release_date, date_mon_accepted;

    cout << "Please enter following parameters for new Textbook:" << endl;
    cout << "Textbook heading:" << endl;
    input = handleInput(isValidText);
    tb.setHeading(input);

    cout << "Textbook price:" << endl;
    input = handleInput(isNonNegativeNumber);
    tb.setPrice(stoi(input));

    cout << "Textbook Authors Count:" << endl;
    input = handleInput(isNonNegativeNumber);
    for (int i = 0; i < stoi(input); i++) {
        string author;
        cout << "Textbook Author " << i << " name:" << endl;
        author = handleInput(isValidText);
        tb.addAuthorToAuthors(author);
    }
    cout << "Textbook edition:" << endl;
    input = handleInput(isNonNegativeNumber);
    tb.setEdition(stoi(input));

    cout << "Textbook ISBN number:" << endl;
    input = handleInput(isNonNegativeNumber);
    tb.setIsbnNumber(input);

    cout << "Textbook Print Run:" << endl;
    input = handleInput(isNonNegativeNumber);
    tb.setPrintRun(stoi(input));

    cout << "Textbook release date (Year-Month-Date):" << endl;
    input = handleInput(isValidDate);
    // Convert string to tm struct
    istringstream ss(input);
    ss >> get_time(&release_date, "%Y-%m-%d");
    tb.setReleaseDate(release_date);

    cout << "Is Textbook Accepted by MON (True/False):" << endl;
    input = handleInput(isValidBool);
    bool mon_accepted = stringToBool(input);
    tb.setIsMonAccepted(mon_accepted);

    if (mon_accepted) {
        cout << "Textbook MON acception date (Year-Month-Date):" << endl;
        input = handleInput(isValidDate);
        // Convert string to tm struct
        istringstream ss(input);
        ss >> get_time(&date_mon_accepted, "%Y-%m-%d");
        tb.setDateMonAccepted(date_mon_accepted);
    }
    
    all_textbooks.push_back(tb);
    new_textbook_added = true;
}

void handleAddNewBookseller() {
    string input;
    Bookseller bs;
    cout << "Please enter name, address and phone number for the new bookseller:" << endl;
    cout << "Bookseller name:" << endl;
    input = handleInput(isValidText);
    bs.setName(input);
    
    cout << "Bookseller address:" << endl;
    input = handleInput(isValidText);
    bs.setAddress(input);

    cout << "Bookseller phone number:" << endl;
    input = handleInput(isValidPhoneNumber);
    bs.setPhoneNumber(input);

    all_booksellers.push_back(bs);
    new_bookseller_added = true;
}

void displayAllTextbooks() {
    cout << "\\/=== All Textbooks ===\\/" << endl;
    for (const Textbook& textbook : all_textbooks) {
        cout << textbook << endl;
        cout << endl;
    }
    system("pause");
}

void displayAllBooksellers() {
    cout << "\\/=== All Booksellers ===\\/" << endl;
    for (const Bookseller& bookseller : all_booksellers) {
        cout << bookseller << endl;
        cout << endl;
    }
    system("pause");
}

void handleCreateNewOrder() {
    Order order;
    handleSelectBookseller(order);
    handleSelectTextbooks(order);
    calculateTotalOrderPrice(order);
    system("pause");
}

void handleSelectBookseller(Order& order) {
    cout << "Enter bookseller ID to choose it:" << endl;
    size_t i;
    for (i = 0; i < all_booksellers.size(); ++i) {
        cout << i << ": " << all_booksellers[i].getName() << endl;
    }
    string input = handleInput(isNonNegativeNumber);
    size_t index = stoi(input);
    if (index < all_booksellers.size()) {
        cout << "Bookseller '" << all_booksellers[index].getName() << "' selected." << endl;
        order.setBookseller(all_booksellers[index]);
    } else {
        cout << "Invalid selection." << endl;
    }
}

void handleSelectTextbooks(Order& order) {
    cout << "Select textbooks to order:" << endl;
    for (size_t i = 0; i < all_textbooks.size(); ++i) {
        cout << i << ": " << all_textbooks[i].getHeading() << " - " << all_textbooks[i].getPrice() << endl;
    }
    string input;
    while (true) {
        cout << "Enter textbook index (or type 'done' to finish):" << endl;
        getline(cin, input);
        if (input == "done") break;
        size_t index = stoi(input);
        if (index < all_textbooks.size()) {
            order.addTextbookToOrder(all_textbooks[index]);
            cout << "Textbook " << all_textbooks[index].getHeading() << " added to order." << endl;
        } else {
            cout << "Invalid selection." << endl;
        }
    }
}

void calculateTotalOrderPrice(Order& order) {
    int totalPrice = 0;
    for (const Textbook& textbook : order.getOrderedTextbooks()) {
        totalPrice += textbook.getPrice();
    }
    cout << "Total Order Price: " << totalPrice << " for Bookseller '" << order.getBookseller().getName() << "'" << endl;
}
