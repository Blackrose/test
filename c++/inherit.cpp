#include<iostream>
using namespace std;

class base{
public:
    base():mem('0')
    {

    }
virtual void  display()
{
    cout<< " I am base"<<endl;
}
protected:
    char    mem;
};

class derive :public base {
public:
    derive():mem('1')
    {

    }
virtual void  display()
{
    cout<< " I am drive"<<endl;
}
    char getmem()
    {
        return mem;
    }
    char getbasemem()
    {
        return base::mem;
    }
protected :
    char mem;
};

int main()
{

    derive test;
    cout<<"the mem may be the derive :" << test.getmem() << endl;
    cout<<"the mem may be the base: " << test.getbasemem() << endl;
    base *p_test = &test;
    p_test->display();
    test->getmem();
    return 0;
}
