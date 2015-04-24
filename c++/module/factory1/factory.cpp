#include "factory.h"
#include "Product.h"
#include <iostream>
using namespace std;
Factory::Factory()
{
   LOGFUNC;
}
/*Factory::~Factory()
{
    LOGFUNC;
}*/



ConCreateFactory::ConCreateFactory()
{
    LOGFUNC;
}

ConCreateFactory::~ConCreateFactory()
{
    LOGFUNC;
}

Product* ConCreateFactory::CreateProduce()
{
    return new ConcreateProduct();
    LOGFUNC;
}
Product* ConCreateFactory::CreateProduceBook()
{
    LOGFUNC;
    return new ConcreateProductBook();
}
