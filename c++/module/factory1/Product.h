#ifndef _PRODUCT_H_
#define _PRODUCT_H_
class Product
{
    /* the destruction of base class shoule the virtual functtion
    =0 that let the bass class cant not to create*/
public:
    virtual ~Product() = 0;
    virtual void display() = 0;
protected:
    Product();
};

class ConcreateProduct: public Product
{
public:
    ~ConcreateProduct();
    ConcreateProduct();
    virtual void display();
};

class ConcreateProductBook : public Product
{
public:
    ~ConcreateProductBook();
    ConcreateProductBook();
    virtual void display();
};

#define LOGFUNC  cout<<__PRETTY_FUNCTION__<<endl
#endif
