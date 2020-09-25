#ifndef SOLID
#define SOLID

#include <math.h>
#include <string>

class Solid {
    public:
    virtual double bottomArea() const = 0;
    virtual double volume() const = 0;
    virtual void add(Solid *s){}
    virtual int numberOfChild(){
        return -1;
    }
    virtual std::vector<Solid*> find(double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){}

    virtual std::vector<Solid*> s_find(Solid* solid, double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){}

    virtual double bottomArea_composite_has_child(Solid* solid){}

    virtual double volumn_composite_has_child(Solid* solid){}

    virtual Solid* getSolid(int i){}
};

#endif