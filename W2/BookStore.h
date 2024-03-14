#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <iomanip>
#include <string>
#include <vector>
#include "Book.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

struct BookHash
{
    std::size_t operator()(const Book &b) const
    {
        // Compute individual hash values for two data members and combine them using XOR and bit shifting
        return std::hash<std::string>()(b.getTitle()) ^ (std::hash<std::string>()(b.getAuthor()) << 1);
    }
};

struct BookEqual
{
    bool operator()(const Book &lhs, const Book &rhs) const
    {
        return lhs.getTitle() == rhs.getTitle() && lhs.getAuthor() == rhs.getAuthor();
    }
};

class BookStore
{
private:
    string name;
    vector<Book> data;
    unordered_map<Book, int, BookHash, BookEqual> cart;

public:
    BookStore() {}
    void init(string dataPath);
    void addBookUtil(Book newBook);
    void addBook();
    Book viewBookAt(int pos);
    vector<Book> sortByPrice();
    vector<Book> sortByDate();
    vector<Book> sortByStockLevel();

    void viewSortedPriceList();
    void viewTopK(int k = 10);
    void addToCart();
    void viewCart(ostream &output, float total);
    void viewStock(string ISBN);
    float checkout();
    void saveBill(float total);
    int getNumberOfBooks();
    void displayLowStockBooks(int defaultStockLevel = 50);
    void menu();
    string getStoreName();
    void clearCart();
    
};

#endif