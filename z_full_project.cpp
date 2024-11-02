// TODO LIST
// DONE: Separate into files

// Да има възможност за избор на книгоразпространител и за него да се порычват различни 
// учебници, като се изчислява общата цена на порьчката

// DONE: Необходимо е да извършвате проверка на входните данни

// DONE: Данните да се четат и съхраняват във файл

// Класовете да се опишат с UML клас диаграма

// Да се изготви документация, която да се предаде по време на зашитата на проекта!


#include <iostream>
#include <vector>
#include <conio.h> // Изисква се за използване на getch() в Windows
#include <map>
#include <functional>  // for the function template
#include <ctime>
#include <iomanip> // For get_time
#include <fstream>
// From GITHUB nlohmann/json: JSON for Modern C++
// used for reading/writing to JSON file
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#define KEYBOARD_BUTTON_UP      72
#define KEYBOARD_BUTTON_DOWN    80
#define KEYBOARD_BUTTON_ENTER   13
#define KEYBOARD_CTRL_C         3
#define KEYBOARD_ESC            27

#define TEXTBOOKS_FILENAME   "textbooks.json"
#define BOOKSELLERS_FILENAME "booksellers.json"

static bool isValidText(const string& input);
static bool isValidNumber(const string& input);
static bool isValidString(const string& input);
static bool isValidPhoneNumber(const string& phone_number);
static bool isNonNegativeNumber(const string& input);
static bool isValidDate(const string& input);
static bool isValidBool(string& input);
static string handleInput(function<bool(string&)> validator);
static bool stringToBool(string& str);
static void handleAddNewTextbook();
static void handleAddNewBookseller();
static void displayAllTextbooks();
static void displayAllBooksellers();

// Предефинираме оператора << за всякакъв тип вектори като използваме темплейт
// Това помага за улеснено принтиране на колекциите от учебници и книгоразпространители
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
// Предефинираме оператора << за структурата tm за да можем по - лесно да принтираме датите
ostream& operator<<(ostream& os, const tm& time) {
    os << put_time(&time, "%Y-%m-%d");
    return os;
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
    friend void to_json(json& j, const Textbook& tb);
    friend void from_json(const json& j, Textbook& tb);
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
void to_json(json& j, const Textbook& tb) {
    j = json{
        {"heading", tb.heading},
        {"authors", tb.authors},
        {"edition", tb.edition},
        {"isbn_number", tb.isbn_number},
        {"print_run", tb.print_run},
        {"release_date", {tb.release_date.tm_year + 1900, tb.release_date.tm_mon + 1, tb.release_date.tm_mday}},
        {"is_mon_accepted", tb.is_mon_accepted},
        {"date_mon_accepted", {tb.date_mon_accepted.tm_year + 1900, tb.date_mon_accepted.tm_mon + 1, tb.date_mon_accepted.tm_mday}},
        {"price", tb.price}
    };
}
void from_json(const json& j, Textbook& tb) {
    j.at("heading").get_to(tb.heading);
    j.at("authors").get_to(tb.authors);
    j.at("edition").get_to(tb.edition);
    j.at("isbn_number").get_to(tb.isbn_number);
    j.at("print_run").get_to(tb.print_run);
    auto release_date = j.at("release_date");
    tb.release_date.tm_year = release_date[0].get<int>() - 1900; // Year since 1900
    tb.release_date.tm_mon = release_date[1].get<int>() - 1; // 0-11 for months
    tb.release_date.tm_mday = release_date[2].get<int>(); // Day of the month

    j.at("is_mon_accepted").get_to(tb.is_mon_accepted);
    
    // Extract the date_mon_accepted array
    auto date_mon_accepted = j.at("date_mon_accepted");
    tb.date_mon_accepted.tm_year = date_mon_accepted[0].get<int>() - 1900;
    tb.date_mon_accepted.tm_mon = date_mon_accepted[1].get<int>() - 1;
    tb.date_mon_accepted.tm_mday = date_mon_accepted[2].get<int>();

    j.at("price").get_to(tb.price);
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
    friend void to_json(json& j, const Bookseller& bs);
    friend void from_json(const json& j, Bookseller& tb);
};
ostream& operator<<(ostream& os, const Bookseller& bs) {
    os << "Bookseller Name: " << bs.getName() << "\n"
       << "Address: " << bs.getAddress() << "\n"
       << "Phone Number: " << bs.getPhoneNumber();
    // Return the output stream to allow chaining
    return os;
}
void to_json(json& j, const Bookseller& bs) {
    j = json{
        {"name", bs.name},
        {"address", bs.address},
        {"phone_number", bs.phone_number}
    };
}
void from_json(const json& j, Bookseller& bs) {
    j.at("name").get_to(bs.name);
    j.at("address").get_to(bs.address);
    j.at("phone_number").get_to(bs.phone_number);
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

static void handleAddNewTextbook() {
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

static void handleAddNewBookseller() {
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

void saveTextbooksToFile(const string& filename) {
    // Тук можем директно да сериализираме обекта към JSON защото предефинирахме функциите 
    // to_json и from_json, както например се предефинира оператор
    json j = all_textbooks;
    ofstream file(filename);
    if (file.is_open()) {
        // Идентираме файла с 1 таб разстояние и записваме JSON обекта
        file << setw(4) << j;
        file.close();
    } else {
        cout << "There was error opening the Textbooks file.";
    }
}

vector<Textbook> loadTextbooksFromFile(const string& filename) {
    vector<Textbook> textbooks;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open the file: " << filename << endl;
        return textbooks;
    }

    json j;
    file >> j;
    for (const auto& item : j) {
        textbooks.push_back(item.get<Textbook>());
    }

    return textbooks;
}

void saveBooksellersToFile(const string& filename) {
    // Тук можем директно да сериализираме обекта към JSON защото предефинирахме функциите 
    // to_json и from_json
    json j = all_booksellers;
    ofstream file(filename);
    if (file.is_open()) {
        // Идентираме файла с 1 таб разстояние и записваме JSON обекта
        file << setw(4) << j;
        file.close();
    } else {
        cout << "There was error opening the Booksellers file.";
    }
}

vector<Bookseller> loadBooksellersFromFile(const string& filename) {
    vector<Bookseller> booksellers;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open the file: " << filename << endl;
        return booksellers;
    }

    json j;
    file >> j;
    for (const auto& item : j) {
        booksellers.push_back(item.get<Bookseller>());
    }

    return booksellers;
}


static void writeNewDataToFile() {
    if (!new_bookseller_added && !new_textbook_added) {
        return;
    }
    
    if (new_bookseller_added) {
        new_bookseller_added = false;
        saveBooksellersToFile(BOOKSELLERS_FILENAME);
    }
    if (new_textbook_added) {
        new_textbook_added = false;
        saveTextbooksToFile(TEXTBOOKS_FILENAME);
    }
}


static bool isValidString(const string& input) {
    return !input.empty();
}

static bool isValidText(const string& input) {
    return isValidString(input) && !isValidNumber(input);
}

static bool isValidNumber(const string& input) {
    if (!isValidString(input)) return false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

static bool isNonNegativeNumber(const string& input) {
    if (!isValidString(input)) return false;
    if (!isValidNumber(input)) return false;
    if (input[0] == '-') return false;
    
    return true;
}

static bool isValidPhoneNumber(const string& input) {
    // Check if the phone number is non-empty and contains only digits or starts with '+'
    if (input.empty()) return false;
    for (size_t i = 0; i < input.size(); ++i) {
        if (!isdigit(input[i]) && (i != 0 || input[i] != '+')) {
            return false;  // Invalid character found
        }
    }
    return true;
}

static bool isValidDate(const string& input) {
    istringstream ss(input);
    tm date = {};

    ss >> get_time(&date, "%Y-%m-%d");

    /*
    Stream Failure Flag (failbit):
    When using input streams in C++ (like std::istringstream), the fail() function returns true if a 
    read or parse operation did not complete successfully.
    This can happen if the input string doesn’t match the expected format.
    */
    if (ss.fail())
        return false;

    // Зададените стойности за ден месец, година не са валидни
    if (date.tm_year < 0 || date.tm_mon < 0 || date.tm_mon > 11 || date.tm_mday < 0 || date.tm_mday > 31)
        return false;

    // Не е краят на стрийма, тоест има още символи извън необходимите
    if (!ss.eof())
        return false;

    return true;
}

static bool isValidBool(string& input) {
    if (!isValidString(input)) return false;
    for_each(input.begin(), input.end(), [](char &c) {
        c = tolower(c);
    });
    if (input == "true" || input == "yes" || input == "1" ||
        input == "false" || input == "no" || input == "0") {
            return true;
        }
    return false;
}

static bool stringToBool(string& str) {
    for_each(str.begin(), str.end(), [](char &c) {
        c = tolower(c);
    });
    return (str == "true" || str == "1" || str == "yes");
}

static string handleInput(function<bool(string&)> validator) {
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


int main() {

    ConsoleMenu menu;
    // Зареждаме вече запазените във файловете данни
    all_booksellers = loadBooksellersFromFile(BOOKSELLERS_FILENAME);
    all_textbooks = loadTextbooksFromFile(TEXTBOOKS_FILENAME);

    while(true) {
        menu.displayMenu();
        menu.handleUserInput();
        writeNewDataToFile();
    }

    return 0;
}