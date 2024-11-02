#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "textbook.h"
#include "bookseller.h"

using namespace std;


void saveTextbooksToFile(const string& filename);

vector<Textbook> loadTextbooksFromFile(const string& filename);

void saveBooksellersToFile(const string& filename);

vector<Bookseller> loadBooksellersFromFile(const string& filename);

void writeNewDataToFile();


#endif //FILE_MANAGER_H