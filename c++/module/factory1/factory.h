#ifndef FACTORY_H
#define FACTORY_H
#include "Product.h"
class Factory
{
public:
    //~Factory() = 0;
    virtual Product* CreateProduce() = 0;
    virtual Product* CreateProduceBook() = 0;
protected:
    Factory();
};

class ConCreateFactory:public Factory
{
public:
    ConCreateFactory();
    ~ConCreateFactory();
    Product* CreateProduce();
    Product*CreateProduceBook();
};


#endif // FACTORY_H
