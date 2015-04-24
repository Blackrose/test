#include "hasptr.h"

int main(int argc,char *argv[])
{
    HasPtr test = HasPtr(new int(3), 1);
    HasPtr testcop = HasPtr(test);
    HasPtr testcop1 = testcop;
    return 0;
}
