#ifndef ORDER_H
#define ORDER_H

#include "order.h"
#include "bookseller.h"
#include "textbook.h"

class Order {
private:
    Bookseller bookseller;
    vector<Textbook> ordered_textbooks;

public:
    /**
     * @brief Празен конструктор на класа `Order`.
     * @param none void
     * @return Order
     */
    Order();

    /**
     * @brief Getter функция за `bookseller` параметъра на класа `Order`.
     * @param none void
     * @return Bookseller - Инстанцията на класа `Bookseller`, обвързана с поръчката.
     */
    Bookseller getBookseller();

    /**
     * @brief Setter функция за `bookseller` параметъра на класа `Order`.
     * @param bs Bookseller - Инстанция на класа `Bookseller`, която ще бъде добавена към поръчката.
     * @return void
     */
    void setBookseller(Bookseller bs);

    /**
     * @brief Getter функция за `ordered_textbooks` параметъра на класа `Order`.
     * @param none void
     * @return vector<Textbook> - Списък с всички поръчани учебници в поръчката
     */
    vector<Textbook> getOrderedTextbooks();

    /**
     * @brief Добавя нов учебник към списъка с поръчани учебници в класа Order.
     * 
     * Функцията append-ва дадена инстанция на `Textbook` класа във вектора `ordered_textbooks` 
     * на `Order` класа.
     * @param tb Textbook - Инстанция на класа `Textbook`, която ще бъде добавена към поръчката.
     * @return void
     */
    void addTextbookToOrder(Textbook tb);
};

#endif //ORDER_H
