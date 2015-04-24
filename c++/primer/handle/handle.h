#ifndef HANDLE_H
#define HANDLE_H
#include "log.h"
#include "string"
using namespace std;
class handle
{
public:
    handle();
};

class SalesBase{
public:
    SalesBase()
    {
        LOGFUNC;
    }
    SalesBase(string bn = "", double price = 0.0):mBn(bn),mPrice(price) { LOGFUNC; }

    SalesBase(const SalesBase& orig)
    {
        mBn = orig.mBn;
        mPrice = orig.mPrice;
    }

    ~SalesBase()
    {

    }
    virtual SalesBase* clone() const {
        return new SalesBase(*this);
    }
private:
    string mBn;
protected:
    double mPrice;
};

class SalesIterm
{
public:
    /*
        it will create the p to NULL
        if want chage the p msut pass the SaleBase or a SalesIterm
        the use must init 1, for the ~SalesIterm()
    */
    SalesIterm():p(0), use(new std::size_t(1)){LOGFUNC;}

    SalesIterm(const SalesBase&);

    SalesIterm(const SalesIterm& i):p(i.p),use(i.use){ *use++; LOGFUNC;}
    ~SalesIterm(){  decrUse();  LOGFUNC;;}
    SalesIterm& operator=(const SalesIterm&);
    const SalesBase* operator->() const
    {
        LOGFUNC;
        if(p) return p;
    }
    const SalesBase  &operator*() const
    {
        if(p) return *p;
    }


private:
    SalesBase *p;
    std::size_t *use;
    void decrUse()
    {
        /* use must initial to one*/
        if(--*use == 0){delete p; delete use;}
    }

};

#endif // HANDLE_H
