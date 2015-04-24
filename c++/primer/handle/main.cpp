#include "handle.h"

void func(SalesIterm& orig)
{
    const SalesBase test = SalesBase(string("1-3-4-56-54"), 19.0);
    SalesIterm temp =SalesIterm(test);
    orig = temp;
}

int main(int argc, char *argv[])
{
    int *p = new int(1);

    SalesIterm test;
    func(test);

}
