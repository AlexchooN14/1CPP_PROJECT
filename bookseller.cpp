#include "bookseller.h"
#include <iostream>
// From GITHUB nlohmann/json: JSON for Modern C++
// used for reading/writing to JSON file
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


Bookseller::Bookseller() {}
Bookseller::Bookseller(string name, string address, string phone_number) {
    setName(name);
    setAddress(address);
    setPhoneNumber(phone_number);
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

ostream& operator<<(ostream& os, const Bookseller& bs) {
    os << "Bookseller Name: " << bs.name << "\n"
       << "Address: " << bs.address << "\n"
       << "Phone Number: " << bs.phone_number;

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
