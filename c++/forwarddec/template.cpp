#include <iostream>
using namespace std;

template <typename T>
void display(T arg)
{
    cout<<" the lengh of arg is"<< sizeof(arg)<<endl;
}

int main()
{
    cout<< "float"<< endl;
    float f_test;
    display(f_test);
    char c_test;
    display(c_test);
}
