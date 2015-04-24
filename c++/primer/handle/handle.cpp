#include "handle.h"

handle::handle()
{

}
/* 接受 对象的复制构造函数 */
SalesIterm::SalesIterm(const SalesBase& orig)
{
    LOGFUNC;
    p = orig.clone();
    use = new std::size_t(1);
}

SalesIterm& SalesIterm::operator =(const SalesIterm& rhs)
{
    ++*(rhs.use);
    decrUse();
    p = rhs.p;
    use = rhs.use;
    return *this;
}
