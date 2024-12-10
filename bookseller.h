#ifndef BOOKSELLER_H
#define BOOKSELLER_H

#include <iostream>
#include <string>
// Външна библиотека, позволяваща използването на JSON файлов формат
// GITHUB nlohmann/json
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Bookseller {
private:
    string name;
    string address;
    string phone_number;

public:
    string getName() const;
    void setName(string name);
    string getAddress() const;
    void setAddress(string address);
    string getPhoneNumber() const;
    void setPhoneNumber(string phone_number);

    Bookseller();
    Bookseller(string name, string address, string phone_number);

    friend ostream& operator<<(ostream& os, const Bookseller& bs);
    friend void to_json(json& j, const Bookseller& bs);
    friend void from_json(const json& j, Bookseller& tb);
};

#endif // BOOKSELLER_H
