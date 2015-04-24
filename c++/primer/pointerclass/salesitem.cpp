#include "salesitem.h"

SalesItem::SalesItem():p(0),use(new std::size_t(1))
{

}

SalesItem::SalesItem(const SalesItem& orig)
{

}

SalseBase& operator= (const SalesItem& rhs)
{

}

SalesItem::~SalesItem()
{
    if(--*use == 0)
    {
        delete p;
        delete use;
    }
}
