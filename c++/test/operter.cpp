#include<iostream>
#include<log.h>
class Verhicle
{
public:
    Verhicle()
    {
        LOGFUNC;
    }
    ~Verhicle()
    {
        LOGFUNC;
    }
};
class VerhicleSurrogate
{
public:
    VerhicleSurrogate()
    {
        LOGFUNC;
    }
    VerhicleSurrogate(const Verhicle& orig)
    {
        LOGFUNC;
    }
    VerhicleSurrogate(const VerhicleSurrogate& orig)
    {
        LOGFUNC;
    }
    VerhicleSurrogate& operator=(const VerhicleSurrogate& orig)
    {
        LOGFUNC;
        return *this;
    }
    ~VerhicleSurrogate()
    {
        LOGFUNC;
    }

};

int main()
{
    VerhicleSurrogate parklot[100];
    Verhicle x;
    parklot[0] = x;
    LOGFUNC;
}
