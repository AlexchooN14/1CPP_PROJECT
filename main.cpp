#include "main.h"
#include "console_menu.h"
#include "file_manager.h"
using namespace std;


vector<Bookseller> all_booksellers;
vector<Textbook> all_textbooks;
bool new_bookseller_added = false;
bool new_textbook_added = false;

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
