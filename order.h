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
    Order();
    Bookseller getBookseller();
    void setBookseller(Bookseller bs);
    vector<Textbook> getOrderedTextbooks();
    void addTextbookToOrder(Textbook tb);
};

#endif //ORDER_H
