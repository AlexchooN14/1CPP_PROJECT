#include "bookseller.h"

Bookseller::Bookseller() {
    // Default constructor implementation
}

Bookseller::Bookseller(std::string name, std::string address, std::string phone_number) {
    // Constructor implementation
}

std::ostream& operator<<(std::ostream& os, const Bookseller& bs) {
    // Overloaded output operator implementation
}

string Bookseller::getName() const {
    return this->name;
}
void Bookseller::setName(string name) {
    this->name = name;
}
string Bookseller::getAddress() const {
    return this->address;
}
void Bookseller::setAddress(string address) {
    this->address = address;
}
string Bookseller::getPhoneNumber() const {
    return this->phone_number;
}
void Bookseller::setPhoneNumber(string phone_number) {
    this->phone_number = phone_number;
}
