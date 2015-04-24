#include "hasptr.h"
#include "log.h"
HasPtr::HasPtr(int *p, int i):ptr(new U_Ptr(p)),val(i)
{
    LOGFUNC;
}
HasPtr::HasPtr(const HasPtr& orig)
{
    LOGFUNC;
    val = orig.val;
    ptr =  orig.ptr;
    ptr->use++;
}
HasPtr& HasPtr::operator= (const HasPtr& rhs)
{
    LOGFUNC;
    rhs.ptr->use++;
    if(--ptr->use ==0)
    {
        delete ptr;
    }
    ptr = rhs.ptr;
    val = rhs.val;
    return *this;

}

HasPtr::~HasPtr()
{
    LOGFUNC;
    if(--ptr->use == 0)
    {
        delete ptr;
    }
}
