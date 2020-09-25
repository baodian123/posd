#ifndef TRIANGULAR_PYRAMID
#define TRIANGULAR_PYRAMID
#include "solid.h"

class TriangularPyramid : public Solid{
public:
  TriangularPyramid(double x1, double y1, double x2, double y2, double x3, double y3, double height): _x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3), _height(height){
    if( !isIsoscelesTriangle() ){
      std::string msg = "Bottom is not a Triangle!";
      throw msg;
    }
  }
  double bottomArea() const{
    double a = sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0));
    double b = sqrt(pow((_x3 - _x2), 2.0) + pow((_y3 - _y2), 2.0));
    double c = sqrt(pow((_x3 - _x1), 2.0) + pow((_y3 - _y1), 2.0));
    double s = (a + b + c) * 0.5;

    return sqrt(s * (s - a) * (s - b) * (s - c));

  }
  double volume() const{
    double a = sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0));
    double b = sqrt(pow((_x3 - _x2), 2.0) + pow((_y3 - _y2), 2.0));
    double c = sqrt(pow((_x3 - _x1), 2.0) + pow((_y3 - _y1), 2.0));
    double s = (a + b + c) / 2.0;

    return sqrt(s * (s - a) * (s - b) * (s - c)) * _height / 3.0;
  }

  bool isIsoscelesTriangle(){
    double a = sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0));
    double b = sqrt(pow((_x3 - _x2), 2.0) + pow((_y3 - _y2), 2.0));
    double c = sqrt(pow((_x3 - _x1), 2.0) + pow((_y3 - _y1), 2.0));

    return (((((a + b) > c)) && (((b + c) > a)) && (((a + c) > b))) && (a > 0 && b > 0 && c > 0));
  }

  std::vector<Solid*> find(double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){
    std::vector<Solid*> s1;
    double a = sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0));
    double b = sqrt(pow((_x3 - _x2), 2.0) + pow((_y3 - _y2), 2.0));
    double c = sqrt(pow((_x3 - _x1), 2.0) + pow((_y3 - _y1), 2.0));
    double s = (a + b + c) / 2.0;

    double bottom = sqrt(s * (s - a) * (s - b) * (s - c));
    double volumn = sqrt(s * (s - a) * (s - b) * (s - c)) * _height / 3.0;

    if(bottom <= bottomAreaMax && bottom >= bottomAreaMin && volumn <= volumnMax && volumn >= volumnMin){
      s1.push_back(this);
    }

    return s1;
  }

private:
  double _x1;
  double _y1;
  double _x2;
  double _y2;
  double _x3;
  double _y3;
  double _height;
};

#endif