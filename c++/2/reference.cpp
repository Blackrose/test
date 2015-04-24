#include <iostream>
using namespace std;
int test1 = 0;
int &test2 =  test1;

int main()
{
    cout << test1 << endl;
    test2 = 3;
    cout << "test" <<endl;
    cout << test1 << endl;
}




