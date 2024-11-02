#ifndef UTILS_H
#define UTILS_H

#define KEYBOARD_BUTTON_UP      72
#define KEYBOARD_BUTTON_DOWN    80
#define KEYBOARD_BUTTON_ENTER   13
#define KEYBOARD_CTRL_C         3
#define KEYBOARD_ESC            27

#define TEXTBOOKS_FILENAME   "textbooks.json"
#define BOOKSELLERS_FILENAME "booksellers.json"

#include <iostream>
#include <string>
#include <vector>
// for put_time
#include <iomanip>

using namespace std;

// Предефинираме оператора << за всякакъв тип вектори като използваме темплейт
// Това помага за улеснено принтиране на колекциите от учебници и книгоразпространители
// Предефинираме оператора << за всякакъв тип вектори като използваме темплейт
// Това помага за улеснено принтиране на колекциите от учебници и книгоразпространители
template <typename T>
inline ostream& operator<<(ostream& os, const vector<T>& vec) {
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
inline ostream& operator<<(ostream& os, const tm& time) {
    os << put_time(&time, "%Y-%m-%d");
    return os;
}

bool isValidText(const string& input);
bool isValidNumber(const string& input);
bool isValidString(const string& input);
bool isValidPhoneNumber(const string& phone_number);
bool isNonNegativeNumber(const string& input);
bool isValidDate(const string& input);
bool isValidBool(string& input);
bool stringToBool(string& str);

#endif // UTILS_H