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

public:

    /**
     * @brief Getter функция за `heading` параметъра на класа `Textbook`.
     * @param none void
     * @return string
     */
    string getHeading() const;
    void setHeading(string heading);

    /**
     * @brief Getter функция за `authors` параметъра на класа `Textbook`.
     * @param none void
     * @return vector<string> - Списък от всички автори на `Textbook`
     */
    vector<string> getAuthors() const;
    void addAuthorToAuthors(string author);

    /**
     * @brief Getter функция за `edition` параметъра на класа `Textbook`.
     * @param none void
     * @return int
     */
    int getEdition() const;
    void setEdition(int edition);

    /**
     * @brief Getter функция за `isbn_number` параметъра на класа `Textbook`.
     * @param none void
     * @return string
     */
    string getIsbnNumber() const;
    void setIsbnNumber(string isbn_number);

    /**
     * @brief Getter функция за `print_run` параметъра на класа `Textbook`.
     * @param none void
     * @return int - Тираж на учебника
     */
    int getPrintRun() const;
    void setPrintRun(int print_run);

    /**
     * @brief Getter функция за `release_date` параметъра на класа `Textbook`.
     * @param none void
     * @return tm
     */
    tm getReleaseDate() const;
    void setReleaseDate(tm release_date);

    /**
     * @brief Getter функция за `is_mon_accepted` параметъра на класа `Textbook`.
     * @param none void
     * @return bool - Учебника одобрен ли е от МОН
     */
    bool getIsMonAccepted() const;
    void setIsMonAccepted(bool is_mon_accepted);

    /**
     * @brief Getter функция за `date_mon_accepted` параметъра на класа `Textbook`.
     * @param none void
     * @return tm - Датата, на която учебника е одобрен от МОН
     */
    tm getDateMonAccepted() const;
    void setDateMonAccepted(tm date_mon_accepted);

    /**
     * @brief Getter функция за `price` параметъра на класа `Textbook`.
     * @param none void
     * @return int
     */
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