#ifndef __ELLIPSE__
#define __ELLIPSE__

#include <iostream>
#include <math.h>
#include "shape.h"

class Ellipse:public Shape{
    public:
        Ellipse(double semiMajorAxes,double semiMinorAxes): _semiMajorAxes(semiMajorAxes), _semiMinorAxes(semiMinorAxes){}
        double area() const{
            return M_PI * _semiMajorAxes * _semiMinorAxes;
        }
        double perimeter() const{
            return (2.0 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes));
        }
        double sumOfSquares() const{
            return (pow(M_PI * _semiMajorAxes * _semiMinorAxes, 2.0)
                   + pow((2.0 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes)), 2.0));
        }

    private:
        double _semiMajorAxes;
        double _semiMinorAxes;
};

#endif