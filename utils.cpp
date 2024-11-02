#include "utils.h"
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


bool isValidText(const string& input) {
    return isValidString(input) && !isValidNumber(input);
}

bool isValidString(const string& input) {
    return !input.empty();
}

bool isValidNumber(const string& input) {
    if (!isValidString(input)) return false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

bool isNonNegativeNumber(const string& input) {
    if (!isValidString(input)) return false;
    if (!isValidNumber(input)) return false;
    if (input[0] == '-') return false;
    
    return true;
}

bool isValidPhoneNumber(const string& input) {
    // Check if the phone number is non-empty and contains only digits or starts with '+'
    if (input.empty()) return false;
    for (size_t i = 0; i < input.size(); ++i) {
        if (!isdigit(input[i]) && (i != 0 || input[i] != '+')) {
            return false;  // Invalid character found
        }
    }
    return true;
}

bool isValidDate(const string& input) {
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

bool isValidBool(string& input) {
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

bool stringToBool(string& str) {
    for_each(str.begin(), str.end(), [](char &c) {
        c = tolower(c);
    });
    return (str == "true" || str == "1" || str == "yes");
}