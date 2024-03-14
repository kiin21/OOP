#ifndef BOOK_H
#define BOOK_H

#include "DateTime.h"
#include <iostream>

using namespace std;

class Book
{
private:
    string ISBN;
    string title;
    string author;
    string language;
    int publishedYear;
    int stockLevel;
    float price;
    DateTime inputDate;

public:
    Book() : ISBN(""), title(""), author(""), language(""), publishedYear(0), stockLevel(0), price(0), inputDate(){};

    Book(
        string ISBN, string title, string author, string language, int publishedYear, int stockLevel, float price, DateTime inputDate)
        : ISBN(ISBN), title(title), author(author), language(language), publishedYear(publishedYear),
          stockLevel(stockLevel), price(price), inputDate(inputDate) {}

    Book parseLine(string line);
    bool operator==(const Book &other);
    void increaseStockLevel(int delta = 1);
    void descreaseStockLevel(int delta = 1);
    float getPrice();
    string getTitle() const;
    string getISBN();
    string getAuthor() const;
    int getStockLevel();
    void setInputDate(DateTime inputDate);
    DateTime getInputDate();
    void printBook();
    friend std::ostream &operator<<(std::ostream &os, const Book &book)
    {
        os << book.ISBN << " " << book.title << " " << book.author << " " << book.language << " "
           << book.publishedYear << " " << book.price << " " << book.stockLevel << std::endl;
        return os;
    };
};

#endif