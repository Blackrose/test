#include "Product.h"
#include "factory.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    cout << "In main---->"<<endl;
    Factory *fac =  new ConCreateFactory;
    Product *pro = fac->CreateProduce();
    Product *probook = fac->CreateProduceBook();

    pro->display();
    probook->display();
    cout <<"End main---->"<<endl;
    delete pro;
    delete probook;
    delete fac;
    return 0;
}
