#ifndef FACTORY_H
#define FACTORY_H

#include "product.h""
class Factory{
public:
    virtual ~Factory() = 0;
    virtual Produce* CreateProduct() = 0;
protected:
    Factory(){}

};

Factory ::  ~Factory()
{

}

class CreateBookFactory:public Factory
{
public:
    Produce * CreateProduct()
    {
        return new ProductBook("C++ And Java");
    }
    ~CreateBookFactory(){}

};

class CreateFruitFactory:public Factory
{
public:
    Produce * CreateProduct()
    {
        return new Productfruit("Apple");
    }
    ~CreateFruitFactory(){}

};

#endif // FACTORY_H
