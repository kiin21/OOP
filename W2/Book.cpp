#include "Book.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

Book Book::parseLine(string line)
{
    stringstream ss(line);
    string temp;
    getline(ss, ISBN, ',');
    getline(ss, title, ',');
    getline(ss, author, ',');
    getline(ss, language, ',');
    ss >> publishedYear;

    ISBN.erase(0, 1);
    ISBN.erase(ISBN.size() - 1, 1);
    title.erase(0, 2);
    title.erase(title.size() - 1, 1);
    author.erase(0, 2);
    author.erase(author.size() - 1, 1);
    language.erase(0, 2);
    language.erase(language.size() - 1, 1);

    ss.ignore();
    ss >> price;
    ss.ignore();
    getline(ss, temp, ','); // Read the datetime string
    temp.erase(0, 2);
    temp.erase(temp.size() - 1, 1);
    inputDate = DateTime(temp); // Convert the string to DateTime object
    ss >> stockLevel;
    return Book(ISBN, title, author, language, publishedYear, stockLevel, price, inputDate);
}
bool Book::operator==(const Book &other)
{
    return title == other.title;
}
void Book::increaseStockLevel(int delta)
{
    stockLevel += delta;
}
void Book::descreaseStockLevel(int delta)
{
    stockLevel -= delta;
}
float Book::getPrice()
{
    return price;
}
string Book::getTitle() const
{
    return title;
}
string Book::getISBN()
{
    return ISBN;
}
string Book::getAuthor() const
{
    return author;
}
int Book::getStockLevel()
{
    return stockLevel;
}
void Book::setInputDate(DateTime _inputDate)
{
    inputDate = _inputDate;
}
DateTime Book::getInputDate()
{
    return inputDate;
}
void Book::printBook()
{
    cout << setw(75) << left << title << setw(30) << left << author;
}