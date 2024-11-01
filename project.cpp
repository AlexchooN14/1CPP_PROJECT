#include <iostream>
#include <vector>
#include <conio.h> // Изисква се за използване на _getch() в Windows
#include <map>
#include <functional>  // for the function template
#include <ctime>
#include <iomanip> // For get_time

using namespace std;

#define KEYBOARD_BUTTON_UP      72
#define KEYBOARD_BUTTON_DOWN    80
#define KEYBOARD_BUTTON_ENTER   13
#define KEYBOARD_CTRL_C         3
#define KEYBOARD_ESC            27


static void handleAddNewTextbook();
static void handleAddNewBookseller();
static void displayAllTextbooks();
static void displayAllBooksellers();


template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", "; // Add a comma and space between elements
        }
    }
    os << "]";
    return os;
}
ostream& operator<<(ostream& os, const tm& time) {
    // Using put_time to format the output
    os << put_time(&time, "%Y-%m-%d");
    return os;
}
bool stringToBool(const string& str) {
    for_each(str.begin(), str.end(), [](char &c) {
        c = tolower(c);
    });
    return (str == "true" || str == "1" || str == "yes");
}

class Textbook {
private:
    string heading;
    vector<string> authors;
    int edition;  // Поредно издание
    string isbn_number;
    int print_run;  // Тираж
    tm release_date;
    bool is_mon_accepted = false;
    tm date_mon_accepted;
    int price;
    //  TODO : Add Bookseller somehow ??

public:
    string getHeading() const {
        return this->heading;
    }
    void setHeading(string heading) {
        this->heading = heading;
    }
    vector<string> getAuthors() const {
        return this->authors;
    }
    void addAuthorToAuthors(string author) {
        this->authors.push_back(author);
    }
    int getEdition() const {
        return this->edition;
    }
    void setEdition(int edition) {
        this->edition = edition;
    }
    string getIsbnNumber() const {
        return this->isbn_number;
    }
    void setIsbnNumber(string isbn_number) {
        this->isbn_number = isbn_number;
    }
    int getPrintRun() const {
        return this->print_run;
    }
    void setPrintRun(int print_run) {
        this->print_run = print_run;
    }
    tm getReleaseDate() const {
        return this->release_date;
    }
    void setReleaseDate(tm release_date) {
        this->release_date = release_date;
    }
    bool getIsMonAccepted() const {
        return this->is_mon_accepted;
    }
    void setIsMonAccepted(bool is_mon_accepted) {
        this->is_mon_accepted = is_mon_accepted;
    }
    tm getDateMonAccepted() const {
        return this->date_mon_accepted;
    }
    void setDateMonAccepted(tm date_mon_accepted) {
        this->date_mon_accepted = date_mon_accepted;
    }
    int getPrice() const {
        return this->price;
    }
    void setPrice(int price) {
        this->price = price;
    }

    Textbook() {}
    Textbook(string heading, int price, int edition, string isbn_number, int print_run, tm release_date,
            bool is_mon_accepted, tm date_mon_accepted) {
        setHeading(heading);
        setPrice(price);
        setEdition(edition);
        setIsbnNumber(isbn_number);
        setPrintRun(print_run);
        setReleaseDate(release_date);
        setIsMonAccepted(is_mon_accepted);
        setDateMonAccepted(date_mon_accepted);
    }

    friend ostream& operator<<(ostream& os, const Textbook& tb);
};
ostream& operator<<(ostream& os, const Textbook& tb) {
    os << "Textbook Heading: " << tb.getHeading() << endl
       << "Price: " << tb.getPrice() << endl
       << "Authors: " << tb.getAuthors() << endl
       << "Edition: " << tb.getEdition() << endl
       << "ISBN Number: " << tb.getIsbnNumber() << endl
       << "Print Run: " << tb.getPrintRun() << endl
       << "Release Date: " << tb.getReleaseDate() << endl
       << "Is MON Accepted: " << tb.getIsMonAccepted() << endl;

    if (tb.getIsMonAccepted()) {
        os << "Date MON Accepted: " << tb.getDateMonAccepted();
    }
    os << endl;
    // Return the output stream to allow chaining
    return os;
}

class Bookseller {
private:
    string name;
    string address;
    string phone_number;

public:
    string getName() const {
        return this->name;
    }
    void setName(string name) {
        this->name = name;
    }
    string getAddress() const {
        return this->address;
    }
    void setAddress(string address) {
        this->address = address;
    }
    string getPhoneNumber() const {
        return this->phone_number;
    }
    void setPhoneNumber(string phone_number) {
        this->phone_number = phone_number;
    }

    Bookseller() {}
    Bookseller(string name, string address, string phone_number) {
        setName(name);
        setAddress(address);
        setPhoneNumber(phone_number);
    }

    friend ostream& operator<<(ostream& os, const Bookseller& bs);
};
ostream& operator<<(ostream& os, const Bookseller& bs) {
    os << "Bookseller Name: " << bs.getName() << "\n"
       << "Address: " << bs.getAddress() << "\n"
       << "Phone Number: " << bs.getPhoneNumber();
    // Return the output stream to allow chaining
    return os;
}

static vector<Bookseller> all_booksellers;
static vector<Textbook> all_textbooks;
static bool new_bookseller_added = false;
static bool new_textbook_added = false;


class ConsoleMenu {
private:
    // Map to keep console menu options and their corresponding function handlers
    map<string, function<void()>> menu_options = {};
    // Променлива в която запазваме индекса на избраната в момента опция от менюто
    int menuOptionActive;

public:
    void setNewActiveMenuOption(int option_number) {
        this->menuOptionActive = option_number;
    }
    int getNewActiveMenuOption() {
        return this->menuOptionActive;
    }

    ConsoleMenu () {
        this->menu_options = {
            {"Add a new Textbook", handleAddNewTextbook},
            {"Add a new Book Seller", handleAddNewBookseller},
            {"Display all Textbooks", displayAllTextbooks},
            {"Display all Book Sellers", displayAllBooksellers},
        };
        setNewActiveMenuOption(0);  // By default the first option of the menu is active
    }

    void displayMenu() {
        system("cls");
        int index = 0;
        if (new_bookseller_added || new_textbook_added) 
            cout << "New data added successfully" << endl;
        for (auto const& menu_option_pair : this->menu_options) {
            cout << (this->menuOptionActive == index ? "> " : "  ") << menu_option_pair.first << endl;
            index++;
        }
    }

    void handleUserInput() {
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
};

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


int main() {

    ConsoleMenu menu;

    while(true) {
        menu.displayMenu();
        menu.handleUserInput();
        writeNewDataToFile();
    }

    return 0;
}