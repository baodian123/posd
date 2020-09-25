#ifndef __SHAPE__
#define __SHAPE__

class Shape{
     public:
     virtual double area() const = 0;
     virtual double perimeter() const = 0;
     virtual double sumOfSquares() const = 0;
}; 

#endif