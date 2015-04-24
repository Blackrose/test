#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
using namespace std;
template <class InputeIterator>

void displayv(InputeIterator b, InputeIterator e)
{
    for(; b != e; b++)
    {
        cout<<" "<<hex<<*b;
    }
    cout<<endl;
}


template <class T>
void displayS(T &b)
{
    typename T::size_type size;
    size = b.size();
    int i;
    b[0] =1;
    for(i = 0; i < size; i++)
    {
        cout <<" "<<b[i];
    }

}


int main()
{
    const  string strdata[] = {"This is", " test", " for", " C++"};
    vector<string> strv(strdata, strdata + sizeof(strdata)/sizeof(string*));

    const int data[] = {1,2,3,4,5,6,7,8,9,0,100};
    std::vector<int> num(data, data + sizeof(data)/sizeof(int)) ;

    const int data1[] = {4,5,6,6,2,31,1,8,9,11,100};
    std::vector<int> num2(data1, data1 + sizeof(data1)/sizeof(int)) ;


    vector<int>::iterator iter = find(num.begin(), num.end(), 100);
    std::cout << "the size if data " << sizeof(data)/sizeof(int) <<endl;
    std::cout << "the size if num vector " << num.size() <<endl;
    if(iter != num.end())
    {
        std::cout << "have find the 100" <<endl;
    }

    cout <<"Test accumulate :" << std::accumulate(num.begin(), num.end(), 0) <<endl;
    string sum = accumulate(strv.begin(), strv.end(), string(""));
    sum += " end.....";
    cout <<"Test string accumulate : " << sum <<endl;

    vector<int>::iterator it = num2.begin();
    int cnt = 0;
    cout<< "The repeate num is :" << endl;
    while( (it = find_first_of(it, num2.end(), num.begin(), num.end())) != num2.end())
    {
        cnt++;
        cout<< " "<<*it;
        it++;
    }
    cout << endl;
    cout <<"The repeate count is " << cnt << endl;

    /*fill test*/
    vector<int> fillv(10);
    cout <<"Test fill,,,,,,"<<endl;
    it = fillv.begin();
    for(; it != fillv.end(); it++)
    {
        cout<<" " << *it;
    }
    cout << endl;
    cout <<"the fill result :" <<endl;
    fill(fillv.begin(), fillv.end(), 0xff);
    displayv(fillv.begin(), fillv.end());
    /*back_inserter*/
    cout<<"Back insert test ......." << endl;
    fill_n(back_inserter(fillv), 10, 0xee);
    displayv(fillv.begin(), fillv.end());

    /*copy*/
    cout <<"Copy .........."<<endl;
    list<int> listl;
    copy(fillv.begin() + 8, fillv.end(), back_inserter(listl));
    displayv(listl.begin(), listl.end());
    const  vector<int> l(10);
    displayS(l);

}



