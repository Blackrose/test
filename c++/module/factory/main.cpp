#include <iostream>
#include <product.h>
#include <string>
#include <factory.h>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Factory *pc = new CreateBookFactory;
    Produce *pb = pc->CreateProduct();
    pb->PrintProductName();

    return 0;
}

