#ifndef BOOKSELLER_H
#define BOOKSELLER_H

#include <string>
#include <iostream>

using namespace std;

class Bookseller {
private:
    string name;
    string address;
    string phone_number;

public:
    Bookseller();
    Bookseller(string name, string address, string phone_number);

    string getName() const;
    void setName(string name);
    string getAddress() const;
    void setAddress(string address);
    string getPhoneNumber() const;
    void setPhoneNumber(string phone_number);

    friend ostream& operator<<(ostream& os, const Bookseller& bs);
};

#endif // BOOKSELLER_H
