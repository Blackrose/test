#include <iostream>
using namespace std;
class Singleton{
    public:
        static Singleton *Instance();
        ~Singleton();
    private:
        static Singleton* _inst;
	protected:
        Singleton();
};
Singleton* Singleton::_inst = 0;

Singleton* Singleton::_inst = 0;
Singleton::Singleton()
{
    cout<< " Singleton..." << endl;
}

Singleton::~Singleton()
{
    cout <<"~Singleton..." << endl;
}

Singleton* Singleton::Instance()
{
    if(_inst == 0)
    {
        _inst = new Singleton();
    }
    return _inst;
}


int main()
{
    Singleton* sgn = Singleton::Instance();
	delete sgn;
    return 0;
}
