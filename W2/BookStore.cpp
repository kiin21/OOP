#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "BookStore.h"

using namespace std;

void BookStore::init(string dataPath)
{
    ifstream fin(dataPath);
    if (fin.is_open())
    {
        getline(fin, name);
        string line;
        while (getline(fin, line))
        {
            Book newBook;
            newBook = newBook.parseLine(line);
            addBookUtil(newBook);
        }
        fin.close();
    }
}
void BookStore::addBookUtil(Book newBook)
{
    bool found = false;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].getISBN() == newBook.getISBN())
        {
            data[i].increaseStockLevel(newBook.getStockLevel());
            data[i].setInputDate(newBook.getInputDate());
            found = true;
            break;
        }
    }
    if (!found)
    {
        data.push_back(newBook);
    }
}
void BookStore::addBook()
{
    cout << "Enter ISBN: ";
    string ISBN;
    getline(cin, ISBN);

    cout << "Enter title: ";
    string title;
    getline(cin, title);

    cout << "Enter author: ";
    string author;
    getline(cin, author);

    cout << "Enter language: ";
    string language;
    getline(cin, language);

    cout << "Enter published year: ";
    int publishedYear;
    cin >> publishedYear;

    cout << "Enter price: ";
    float price;
    cin >> price;
    cin.ignore(); // Ignore the newline character

    // Get the current date and time
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert the current time to a string in the yy-mm-dd hh-mm-ss format
    stringstream ss;
    ss << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
    string currentTimeString = ss.str();
    // Separate the year, month, day, hour, minute, and second
    tm *timeInfo = localtime(&currentTime);
    int year = timeInfo->tm_year + 1900;
    int month = timeInfo->tm_mon + 1;
    int day = timeInfo->tm_mday;
    int hour = timeInfo->tm_hour;
    int minute = timeInfo->tm_min;
    int second = timeInfo->tm_sec;

    DateTime inputDate(year, month, day, hour, minute, second);
    int stockLevel = 1;
    Book newBook(ISBN, title, author, language, publishedYear, stockLevel, price, inputDate);
    addBookUtil(newBook);
    cout << "Book added\n";
}
Book BookStore::viewBookAt(int pos)
{
    return data[pos];
}
vector<Book> BookStore::sortByPrice()
{
    vector<Book> newData = data;
    sort(newData.begin(), newData.end(), [](Book a, Book b)
         { return a.getPrice() < b.getPrice() ||
                  (a.getPrice() == b.getPrice() && a.getTitle() < b.getTitle()); });
    return newData;
}

void BookStore::viewSortedPriceList()
{
    vector<Book> sortedList = sortByPrice();
    int count = 1;
    cout << setw(75) << left << "Title"
         << setw(30) << left << "Author"
         << setw(20) << left << "Price" << endl;
    for (int i = 0; i < sortedList.size(); i++)
    {
        sortedList[i].printBook();
        cout << sortedList[i].getPrice() << " $" << endl;
    }
}
vector<Book> BookStore::sortByDate()
{
    vector<Book> newData = data;
    sort(newData.begin(), newData.end(), [](Book a, Book b)
         { return a.getInputDate() < b.getInputDate(); });
    return newData;
}
void BookStore::viewTopK(int k)
{
    vector<Book> sortedList = sortByDate();
    cout << setw(79) << left << "Title" << setw(30) << left << "Author" << setw(20) << left << "Input Date" << endl;
    int count = 1;
    for (int i = sortedList.size() - 1; i >= sortedList.size() - k; i--)
    {
        cout << count++ << ". ";
        sortedList[i].printBook();
        // cout << setw(20) << left;
        sortedList[i].getInputDate().printDateTime();
        cout << endl;
    }
}
void BookStore::addToCart()
{
    string ISBN, quantity;
    cout << "Enter the ISBN of the book you want to add to cart: ";
    getline(cin, ISBN);
    cout << "Enter the quantity of the book you want to add to cart: ";
    getline(cin, quantity);

    bool found = false, enoughStock = true;

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].getISBN() == ISBN)
        {
            found = true;
            if (cart[data[i]] + stoi(quantity) > data[i].getStockLevel())
            {
                enoughStock = false;
                cout << "Not enough stock for: " << data[i].getTitle() << endl;
                cout << "Current stock: " << data[i].getStockLevel() << endl;
                cout << "Quantity in cart: " << cart[data[i]] + stoi(quantity) << endl;
            }
            else
            {
                cart[data[i]] += stoi(quantity);
            }
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found\n";
    }
    else if (enoughStock)
    {
        cout << "Book added to cart\n";
    }
}
void BookStore::viewCart(ostream &output, float total)
{
    output << "Total: " << total << " $" << endl;
    output << "Title" << setw(75) << "Price" << setw(20) << "Quantity\n";
    for (auto it = cart.begin(); it != cart.end(); it++)
    {
        Book *book = const_cast<Book *>(&it->first);
        output << setw(75) << left << book->getTitle()
               << setw(16) << left << book->getPrice()
               << setw(8) << right << it->second << endl;
    }
}
void BookStore::viewStock(string ISBN)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].getISBN() == ISBN)
        {
            data[i].printBook();
            cout << "Stock level: " << data[i].getStockLevel() << endl;
            return;
        }
    }
    cout << "Book not found\n";
}
float BookStore::checkout()
{
    float total = 0;
    for (auto it = cart.begin(); it != cart.end(); it++)
    {
        Book *book = const_cast<Book *>(&it->first);
        total += book->getPrice() * it->second;
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].getISBN() == book->getISBN())
                data[i].descreaseStockLevel(book->getStockLevel());
        }
    }
    saveBill(total);
    return total;
}
void BookStore::saveBill(float total)
{
    // Read the existing content
    ifstream fin("bills.txt", ios::in);
    stringstream buffer;
    buffer << fin.rdbuf();
    string oldContent = buffer.str();
    fin.close();

    ofstream fout("bills.txt", ios::out);
    fout << "Date: ";
    // Get the current date and time
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert the current time to a string in the yy-mm-dd hh-mm-ss format
    stringstream ss;
    ss << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
    string currentTimeString = ss.str();
    fout << currentTimeString << endl;

    viewCart(fout, total);
    fout << "---------------------------------------------\n";
    fout << oldContent;
    fout.close();
}
void BookStore::clearCart()
{
    cart.clear();
}
vector<Book> BookStore::sortByStockLevel()
{
    vector<Book> newData = data;
    sort(newData.begin(), newData.end(), [](Book a, Book b)
         { return a.getStockLevel() < b.getStockLevel(); });
    return newData;
}
void BookStore::displayLowStockBooks(int defaultStockLevel)
{
    vector<Book> sortedList = sortByStockLevel();
    int count = 1;
    cout << setw(75) << left << "Title"
         << setw(30) << left << "Author"
         << setw(20) << left << "Stock level" << endl;
    for (int i = 0; i < sortedList.size(); i++)
    {
        if (sortedList[i].getStockLevel() < defaultStockLevel)
        {
            sortedList[i].printBook();
            cout << sortedList[i].getStockLevel() << "\n";
        }
    }
}
int BookStore::getNumberOfBooks()
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i].printBook();
    }
    return data.size();
}
void BookStore::menu()
{
    cout << "\nWelcome to \"" << name << "\" book store\n\n";
    do
    {
        cout << "1. Xem danh sach theo gia tang dan\n";
        cout << "2. Xem top sach moi nhat\n";
        cout << "3. Them sach vao kho\n";
        cout << "4. Them sach vao vo hang\n";
        cout << "5. Thanh toan\n";
        cout << "6. Xem sach ban chay (sap het hang)\n";
        cout << "\nEnter your choice: ";
        string choice;
        try
        {
            getline(cin, choice);

            switch (stoi(choice))
            {
            case 1:
            {
                viewSortedPriceList();
                break;
            }
            case 2:
            {
                string K;
                cout << "Enter K or leave it empty (K=10): ";
                getline(cin, K);
                if (K.empty())
                    viewTopK();
                else
                    viewTopK(stoi(K));
                break;
            }
            case 3:
            {
                addBook();
                break;
            }
            case 4:
            {
                addToCart();
                break;
            }
            case 5:
            {
                float total = checkout();
                viewCart(cout, total);
                clearCart();
                break;
            }
            case 6:
            {
                displayLowStockBooks();
                break;
            }
            default:
                cout << "\nInvalid choice\n";
            }
            cout << "\nPress enter to continue";
            cin.ignore();
        }
        catch (exception e)
        {
            cout << "\nInvalid choice\n\n";
        }

    } while (1);
}
string BookStore::getStoreName()
{
    return name;
}
