#include <iostream>
using namespace std;
class base{
    public:
        void baseFunc();
        base();
    protected:
        void baseProtect();
    private:
        void basePrivate();

};
base::base()

{cout<<"---------I>"<<__PRETTY_FUNCTION__<<endl;
    cout<<"base::base"<< endl;
}

void base::baseFunc()
{
    cout<<"base:baseFunc"<< endl;
}

void base::basePrivate()
{
    cout << "base::basePrivate" <<endl;
}
void base::baseProtect()
{
    cout << "base::baseProtect" <<endl;
}


class chrid: base{
};


int main()
{
  base baseIns = base();
  chrid chridIns = chrid();
}

