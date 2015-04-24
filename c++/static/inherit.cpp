#include<iostream>
using namespace std;

class testStacic
{
    public:
        static testStacic*  funcStatic(){
			if(memStatic == NULL)
			{
				memStatic = new testStacic();
			}
			return memStatic;
		}
        testStacic():memNoStatic(0){}
    private:
        static testStacic* memStatic;
        int memNoStatic;
};
testStacic* testStacic::memStatic = NULL;

int main()
{
//	testStacic* inst = testStacic::funcStatic();
    testStacic inst3 =  testStacic();
    testStacic* ins2 =  inst3.funcStatic();

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
