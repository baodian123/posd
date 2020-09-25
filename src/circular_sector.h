#ifndef __CIRCULAR_SECTOR__
#define __CIRCULAR_SECTOR__

#include <iostream>
#include <math.h>
#include "shape.h"

class CircularSector:public Shape{
    public:
        CircularSector(double radius, double degree): _radius(radius), _degree(degree){}
        double area() const{
            return _radius * _radius * M_PI * _degree / 360.0;
        }
        double perimeter() const{
            return _radius * 2.0 + 2.0 * M_PI * _radius * _degree / 360.0;
        }
        double sumOfSquares() const{
            double num_area = _radius * _radius * M_PI * _degree / 360.0;
            double num_perimeter = _radius * 2.0 + 2.0 * M_PI * _radius * _degree / 360.0;
            return (num_area * num_area + num_perimeter * num_perimeter);
        }

    private:
        double _radius;
        double _degree;
};

#endif