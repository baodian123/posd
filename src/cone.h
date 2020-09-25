#ifndef CONE
#define CONE
#include "solid.h"

class Cone : public Solid{
public:
  Cone(double x1,double y1,double x2,double y2, double height): _x1(x1), _x2(x2), _y1(y1), _y2(y2), _height(height){
    double radius = (sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0)));
    if(radius == 0){
      std::string msg = "Bottom is not a Circle!";
      throw msg;
    }
  }
  double bottomArea() const{
    double radius = (sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0)));
    return radius * radius * M_PI;
  }
  double volume() const{
    double radius = (sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0)));
    return radius * radius * M_PI * _height / 3.0;
  }

  std::vector<Solid*> find(double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){
    std::vector<Solid*> s;
    double radius = (sqrt(pow((_x2 - _x1), 2.0) + pow((_y2 - _y1), 2.0)));
    double bottom = radius * radius * M_PI;
    double volumn = radius * radius * M_PI * _height / 3.0;

    if(bottom <= bottomAreaMax && bottom >= bottomAreaMin && volumn <= volumnMax && volumn >= volumnMin){
      s.push_back(this);
    }

    return s;
  }

private:
  double _x1;
  double _x2;
  double _y1;
  double _y2;
  double _height;
};

#endif