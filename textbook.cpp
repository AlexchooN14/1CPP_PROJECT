#include "textbook.h"
#include "main.h"
// From GITHUB nlohmann/json: JSON for Modern C++
// used for reading/writing to JSON file
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Празен конструктор
Textbook::Textbook() {}

// Конструктор с всички данни за класа
Textbook::Textbook(string heading, int price, int edition, string isbn_number, int print_run, tm release_date,
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

string Textbook::getHeading() const {
    return this->heading;
}
void Textbook::setHeading(string heading) {
    this->heading = heading;
}
vector<string> Textbook::getAuthors() const {
    return this->authors;
}
void Textbook::addAuthorToAuthors(string author) {
    this->authors.push_back(author);
}
int Textbook::getEdition() const {
    return this->edition;
}
void Textbook::setEdition(int edition) {
    this->edition = edition;
}
string Textbook::getIsbnNumber() const {
    return this->isbn_number;
}
void Textbook::setIsbnNumber(string isbn_number) {
    this->isbn_number = isbn_number;
}
int Textbook::getPrintRun() const {
    return this->print_run;
}
void Textbook::setPrintRun(int print_run) {
    this->print_run = print_run;
}
tm Textbook::getReleaseDate() const {
    return this->release_date;
}
void Textbook::setReleaseDate(tm release_date) {
    this->release_date = release_date;
}
bool Textbook::getIsMonAccepted() const {
    return this->is_mon_accepted;
}
void Textbook::setIsMonAccepted(bool is_mon_accepted) {
    this->is_mon_accepted = is_mon_accepted;
}
tm Textbook::getDateMonAccepted() const {
    return this->date_mon_accepted;
}
void Textbook::setDateMonAccepted(tm date_mon_accepted) {
    this->date_mon_accepted = date_mon_accepted;
}
int Textbook::getPrice() const {
    return this->price;
}
void Textbook::setPrice(int price) {
    this->price = price;
}

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
