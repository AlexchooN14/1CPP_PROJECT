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
/**
 * @brief Функция, която позволява принтирането на типа `vector`.
 * @param os ostream& - Output Stream, към който ще принтираме
 * @param vec const vector<T>& - Обекта от тип `vector`, който ще принтираме
 * @return ostream&
 */
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
/**
 * @brief Функция, която позволява принтирането на типа `tm`.
 * 
 * Функцията улеснява принтирането на датите.
 * @param os ostream& - Output Stream, към който ще принтираме
 * @param time const tm& - Обекта от тип `tm`, който ще принтираме
 * @return ostream&
 */
inline ostream& operator<<(ostream& os, const tm& time) {
    os << put_time(&time, "%Y-%m-%d");
    return os;
}

/**
 * @brief Функция, която проверява, че подадения `string` параметър не е празен и съдържа единствено текстови символи.
 * 
 * Функцията връща `False` ако в подадения `string` параметър се съдържат числа или е празен.
 * В останалите случаи връща `True`.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isValidText(const string& input);

/**
 * @brief Функция, която проверява, че подадения `string` параметър не е празен и съдържа единствено числови символи.
 * 
 * Функцията връща `False` ако в подадения `string` параметър се съдържат букви или е празен.
 * В останалите случаи връща `True`.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isValidNumber(const string& input);

/**
 * @brief Функция, която проверява, че подадения `string` параметър не е празен.
 * 
 * Функцията връща `False` ако подадения `string` е празен.
 * В останалите случаи връща `True`.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isValidString(const string& input);

/**
 * @brief Функция, която проверява, че подадения `string` параметър не е празен и е валиден телефонен номер.
 * 
 * Функцията връща `False` ако в подадения `string` параметър се съдържат букви или по - малко от 10 символа.
 * В останалите случаи връща `True`.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isValidPhoneNumber(const string& phone_number);

/**
 * @brief Функция, която проверява, че подадения `string` параметър не е празен и съдържа единствено числови символи на отрицателно число.
 * 
 * Функцията връща `False` ако в подадения `string` параметър се съдържат букви или е празен.
 * В останалите случаи връща `True`.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isNonNegativeNumber(const string& input);

/**
 * @brief Функция, която проверява, че подадения `string` параметър не е празен и е валидна дата във формата `YYYY-MM-DD`.
 * 
 * Функцията връща `False` ако в подадения `string` не е в правилен формат или е празен.
 * В останалите случаи връща `True`.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isValidDate(const string& input);

/**
 * @brief Функция, която проверява, че подадения `string` параметър е валиден булев текст `True, False, Yes, No`
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool isValidBool(string& input);

/**
 * @brief Функция, която проверява, че подадения `string` параметър е валиден булев текст `True, False, Yes, No`
 * и връща булевото му съответствие.
 * @param input const string& - `string` който искаме да проверим.
 * @return bool
 */
bool stringToBool(string& str);

#endif // UTILS_H