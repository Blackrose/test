#include <iostream>
using namespace std;
class test
{
    public:
        ~test()
        {
            cout<<__func__ <<endl;
        }
        test(const test& ins)
        {
            cout <<__func__<<" copy"<<endl;
        }
        test(int a)
        {
            cout<<__func__ <<endl;
            ma = a;
        }
        test& operator=(const test& Ins)
        {
            cout<<__func__<<endl;
            ma = Ins.ma;
        }
        void display()
        {
            cout <<"ma is ------>" << ma <<endl;
        }
    private:
        int ma;
};

test A(1);
test B(2);
void testfunc()
{
    test C = test(A);
    B = A;
    B.display();
    A.display();
}
int main()
{
    cout <<"main" <<endl;
    testfunc();
    cout <<"end main"<<endl;
}






