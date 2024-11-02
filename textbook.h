#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <string>
#include <vector>
// From GITHUB nlohmann/json: JSON for Modern C++
// used for reading/writing to JSON file
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Textbook {
private:
    string heading;
    vector<string> authors;
    int edition;  // Поредно издание
    string isbn_number;
    int print_run;  // Тираж
    tm release_date;
    bool is_mon_accepted = false;
    tm date_mon_accepted;
    int price;
    //  TODO : Add Bookseller somehow ??

public:
    string getHeading() const;
    void setHeading(string heading);
    vector<string> getAuthors() const;
    void addAuthorToAuthors(string author);
    int getEdition() const;
    void setEdition(int edition);
    string getIsbnNumber() const;
    void setIsbnNumber(string isbn_number);
    int getPrintRun() const;
    void setPrintRun(int print_run);
    tm getReleaseDate() const;
    void setReleaseDate(tm release_date);
    bool getIsMonAccepted() const;
    void setIsMonAccepted(bool is_mon_accepted);
    tm getDateMonAccepted() const;
    void setDateMonAccepted(tm date_mon_accepted);
    int getPrice() const;
    void setPrice(int price);

    Textbook();
    Textbook(string heading, int price, int edition, string isbn_number, int print_run, tm release_date,
            bool is_mon_accepted, tm date_mon_accepted);

    friend ostream& operator<<(ostream& os, const Textbook& tb);
    friend void to_json(json& j, const Textbook& tb);
    friend void from_json(const json& j, Textbook& tb);
};


#endif // TEXTBOOK_H