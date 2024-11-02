#include "file_manager.h"
#include "main.h"
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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


void writeNewDataToFile() {
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
