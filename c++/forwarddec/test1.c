#include<iostream>
class B;
class A{

    private:
        B &b;
    public:
    A(B &c);
};

class B
{
    public:
        void testfun();

};

A::A(B &c):b(c)
{
//    b.testfun();
}

void B::testfun()
{

}


int main()
{
    B test ;
    A *a = new A(test);
    delete a;
    return 0;
}
