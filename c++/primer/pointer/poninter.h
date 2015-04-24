#ifndef PONINTER_H
#define PONINTER_H
#include "hasptr.h"
#include "log.h"
class U_Ptr
{
private:
    friend class HasPtr;
    int *mp;
    unsigned int use;

    U_Ptr(int *p):mp(p), use(1){LOGFUNC;}

    ~U_Ptr()
    {   LOGFUNC;
        delete mp;
    }

};

#endif // PONINTER_H
