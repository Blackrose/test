#include<iostream>
using namespace std;
template <class T>
int compare(const T v1, const T v2)
{
/*    if(v1 < v2) return -1;
    if(v1 > v2) return 1;
    return 0;
*/
}


template <class T, size_t N> void array_init(T (&parm)[N])
{
    for(size_t i =0; i != N; i++)
    {
        parm[i] = 0;
    }
    cout<< N << endl;
}

template <class T> void pointtest(T b)
{
    T a= "adbfjhdfewjferjkhk";
    cout << b;
    cout << "------" << a <<endl;
}

template <class T1, class T2, class T3>
T1 sum(T2 a, T3 b)
{

}


int main()
{
    compare(1, 0);
    string s1="hi", s2="world";
    char data[100];
    array_init(data);
    const char * data1 = "2343232";
    pointtest(data1);
    sum<int>(1, 1.0);
//    compare("hi", "d");
}
