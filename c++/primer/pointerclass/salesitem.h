#ifndef SALESITEM_H
#define SALESITEM_H
#include "salsebase.h"
class SalesItem
{
public:
    SalesItem():p(0), use(new std::size_t(1)) {}
    SalesItem(const SalesItem&);
    SalesItem& operator= (const SalesItem &);
    ~SalesItem();
    SalesItem& operator-> (const SalesItem&) const;
    SalesItem& operator& (const SalesItem&) const;
private:
    SalseBase *p;
    std::size_t *use;
    void decrUse();
};

#endif // SALESITEM_H
