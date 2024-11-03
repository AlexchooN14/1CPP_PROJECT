#include "order.h"
#include "bookseller.h"
#include "textbook.h"

Order::Order() {}

Bookseller Order::getBookseller() {
    return this->bookseller;
}
void Order::setBookseller(Bookseller bs) {
    this->bookseller = bs;
}
vector<Textbook> Order::getOrderedTextbooks() {
    return this->ordered_textbooks;
}
void Order::addTextbookToOrder(Textbook tb) {
    this->ordered_textbooks.push_back(tb);
}
