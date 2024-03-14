#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "BookStore.h"

using namespace std;

int main()
{
    BookStore myStore;
    myStore.init("input.txt");
    myStore.menu();
    return 0;
}