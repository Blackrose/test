#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
using namespace std;
class Produce
{
public:
     ~Produce(){}
    virtual void PrintProductName() = 0;
protected:
    Produce(){}
};

class ProductBook:public Produce
{
public:
    ProductBook(string id):mIdStr(id)
    {
        cout <<"create book"<<endl;
    }

    ~ProductBook(){}

    void PrintProductName()
    {
        std::cout<<mIdStr <<std::endl;
    }

private:
    string mIdStr;
};



class Productfruit:public Produce
{
public:
    Productfruit(string name):mIdStr(name){}
    ~Productfruit();
    void PrintProductName()
    {
        std::cout<<mIdStr <<std::endl;
    }
private:
    string mIdStr;
};




#endif // PRODUCT_H
