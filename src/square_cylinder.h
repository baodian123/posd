#ifndef SQUARE_CYLINDER
#define SQUARE_CYLINDER

#include "solid.h"

class SquareCylinder : public Solid{
public:
  SquareCylinder(double edge, double height): _edge(edge), _height(height){}
  double bottomArea() const{
    return _edge * _edge;
  }
  double volume() const{
    return _edge * _edge * _height;
  }

  std::vector<Solid*> find(double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){
    std::vector<Solid*> s;
    double bottom = _edge * _edge;
    double volumn = _edge * _edge * _height;

    if(bottom <= bottomAreaMax && bottom >= bottomAreaMin && volumn <= volumnMax && volumn >= volumnMin){
      s.push_back(this);
    }

    return s;
  }

private:
  double _edge;
  double _height;
};

#endif