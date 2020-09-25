#ifndef __TRIANGLE__
#define __TRIANGLE__

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

#include <iostream>
#include <math.h>
#include <string>
#include "shape.h"
#include <string>
using namespace std;

class Triangle:public Shape{
    public:
        Triangle(double x1, double y1, double x2, double y2, double x3, double y3): _x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3){
            if( !isIsoscelesTriangle() ){
                string msg = "Not a IsoscelesTriangle.";
                throw msg;
            }
        }
        // give you three points (x1,y1), (x2,y2), (x3,y3) to calculate area and perimeter
        double area() const{
            double a = sqrt(pow((_x2 - _x1), 2) + pow((_y2 - _y1), 2));
            double b = sqrt(pow((_x3 - _x2), 2) + pow((_y3 - _y2), 2));
            double c = sqrt(pow((_x3 - _x1), 2) + pow((_y3 - _y1), 2));

            double s = (a + b + c) / 2.0;
            
            return sqrt(s * (s - a) * (s - b) * (s - c));
        }
        double perimeter() const{
            return ( sqrt(pow((_x2 - _x1), 2) + pow((_y2 - _y1), 2))
                   + sqrt(pow((_x3 - _x2), 2) + pow((_y3 - _y2), 2))
                   + sqrt(pow((_x3 - _x1), 2) + pow((_y3 - _y1), 2))
                );
        }
        bool isIsoscelesTriangle(){
            double a = sqrt(pow((_x2 - _x1), 2) + pow((_y2 - _y1), 2));
            double b = sqrt(pow((_x3 - _x2), 2) + pow((_y3 - _y2), 2));
            double c = sqrt(pow((_x3 - _x1), 2) + pow((_y3 - _y1), 2));

            return (((((a + b) > c)) && (((b + c) > a)) && (((a + c) > b)))
                   && ((a == b) || (b == c) || (a == c)) && (a > 0 && b > 0 && c > 0)
                   );
        }
        double sumOfSquares() const{
            double a = sqrt(pow((_x2 - _x1), 2) + pow((_y2 - _y1), 2));
            double b = sqrt(pow((_x3 - _x2), 2) + pow((_y3 - _y2), 2));
            double c = sqrt(pow((_x3 - _x1), 2) + pow((_y3 - _y1), 2));

            double s = (a + b + c) / 2.0;

            return ( (sqrt(s * (s - a) * (s - b) * (s - c))) * (sqrt(s * (s - a) * (s - b) * (s - c)))
                   + (a + b + c) * (a + b + c) );
        }
    
    private:
        double _x1;
        double _y1;
        double _x2;
        double _y2;
        double _x3;
        double _y3;
 };

#endif