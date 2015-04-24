#ifndef HASPTR_H
#define HASPTR_H
#include "poninter.h"
class HasPtr
{
public:
    HasPtr(int *p, int i);
    ~HasPtr();
    HasPtr(const HasPtr& orig);
    HasPtr& operator= (const HasPtr& rhd);
private:
    U_Ptr *ptr;
    int val;
};

#endif // HADPTR_H
