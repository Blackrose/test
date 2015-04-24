#include<iostream>
using namespace std;
class StaticM
{
public:
    StaticM(string name)
    {
        cout << "StaticM -------->" << name <<endl;
    }
};

class testStacic
{
    public:
        static void funcStatic(){
			{
                cout << "In func" <<__func__ << endl;
			}
		}
        testStacic()
        {
                cout << "In func" <<__func__ << endl;
        }
    private:
        static  StaticM memStatic;
        int memNoStatic;
};
StaticM inst3 =  StaticM(string("globale--->"));
StaticM  testStacic::memStatic = StaticM(string("class name"));
int main()
{
//	testStacic* inst = testStacic::funcStatic();
    cout <<"In main ------>"<< endl;
    testStacic inst3 =  testStacic();

/*
    derive test;
    cout<<"the mem may be the derive :" << test.getmem() << endl;
    cout<<"the mem may be the base: " << test.getbasemem() << endl;
    base *p_test = &test;
    p_test->display();
    test->getmem();
    return 0;
    */
}
