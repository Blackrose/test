#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> myvector;
    myvector.push_back(10);
    while(myvector.back())
    {
        myvector.push_back(myvector.back() - 1);
    }

    cout << "myvector contains:";
    vector<int>::const_iterator iter = myvector.begin();


    for(;iter != myvector.end(); iter++)
    {
        cout<<' '<< *iter;
        myvector.push_back(10);
    }
    cout << endl;
    for(unsigned i = 0; i < myvector.size(); i++)
        cout<<' '<< myvector[i];
    cout << endl;
}
