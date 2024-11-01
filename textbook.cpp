#include "textbook.h"
#include <iomanip>

using namespace std;

Textbook::Textbook() {}

Textbook::Textbook(string heading, int price, int edition, string isbn_number, int print_run, tm release_date, bool is_mon_accepted, tm date_mon_accepted) {
    setHeading(heading);
    setPrice(price);
    setEdition(edition);
    setIsbnNumber(isbn_number);
    setPrintRun(print_run);
    setReleaseDate(release_date);
    setIsMonAccepted(is_mon_accepted);
    setDateMonAccepted(date_mon_accepted);
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
