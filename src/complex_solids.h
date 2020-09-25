#ifndef COMPLEX_SOLIDS
#define COMPLEX_SOLIDS

#include <vector>
#include "solid.h"

class ComplexSolids : public Solid{
public:
    ComplexSolids(std::vector<Solid*> * solids): _solids(solids){}

    void add(Solid *s){
        _solids->push_back(s);
    }
    int numberOfChild(){
        return _solids->size();
    }

    Solid* getSolid(int i){
        return _solids->at(i);
    }

    std::vector<Solid*> s_find(Solid* solid, double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){
        std::vector<Solid*> s;
        for(int i=0; i<solid->numberOfChild(); i++){
            if(solid->getSolid(i)->bottomArea() <= bottomAreaMax && solid->getSolid(i)->bottomArea() >= bottomAreaMin && solid->getSolid(i)->volume() >= volumnMin && solid->getSolid(i)->volume() <= volumnMax && _solids->at(i)->numberOfChild() == -1){
                s.push_back(solid->getSolid(i));
            }
            else if(solid->getSolid(i)->numberOfChild() > 0){
                std::vector<Solid*> s1 = solid->getSolid(i)->s_find(solid->getSolid(i), volumnMin, volumnMax, bottomAreaMin, bottomAreaMax);
                for(int j=0; j<s1.size(); j++) s.push_back(s1.at(j));
            }
        }
        return s;
    }

    std::vector<Solid*> find(double volumnMin, double volumnMax, double bottomAreaMin, double bottomAreaMax){
        std::vector<Solid*> s;
        for(int i=0; i<_solids->size(); i++){
            if(_solids->at(i)->bottomArea() <= bottomAreaMax && _solids->at(i)->bottomArea() >= bottomAreaMin && _solids->at(i)->volume() <= volumnMax && _solids->at(i)->volume() >= volumnMin && _solids->at(i)->numberOfChild() == -1) s.push_back(_solids->at(i));
            else if(_solids->at(i)->numberOfChild() > 0){
                std::vector<Solid*> s1 = _solids->at(i)->s_find(_solids->at(i), volumnMin, volumnMax, bottomAreaMin, bottomAreaMax);
                for(int j=0; j<s1.size(); j++) s.push_back(s1.at(j));
            }
        }
        return s;
    }

    double bottomArea_composite_has_child(Solid* solid){
        double count = 0;
        for(int i=0; i<solid->numberOfChild(); i++){
            if(solid->getSolid(i)->numberOfChild() == -1){
                count = count + solid->getSolid(i)->bottomArea();
            }
            else if(solid->getSolid(i)->numberOfChild() > 0){
                count = count + solid->getSolid(i)->bottomArea_composite_has_child(solid->getSolid(i));
            }
        }
        return count;
    }

    double volumn_composite_has_child(Solid* solid){
        double count = 0;
        for(int i=0; i<solid->numberOfChild(); i++){
            if(solid->getSolid(i)->numberOfChild() == -1){
                count = count + solid->getSolid(i)->volume();
            }
            else if(solid->getSolid(i)->numberOfChild() > 0){
                count = count + solid->getSolid(i)->volumn_composite_has_child(solid->getSolid(i));
            }
        }
        return count;
    }

    double bottomArea() const{
        double count = 0;
        for(int i=0; i<_solids->size(); i++){
            if(_solids->at(i)->numberOfChild() == -1){  //leaf
                count = count + _solids->at(i)->bottomArea();
            }
            else if(_solids->at(i)->numberOfChild() > 0){ //composite has child
                count = count + _solids->at(i)->bottomArea_composite_has_child(_solids->at(i));
            }
        }
        
        return count;
    }
    double volume() const{
        double count = 0;
        for(int i=0; i<_solids->size(); i++){
            if(_solids->at(i)->numberOfChild() == -1){  //leaf
                count = count + _solids->at(i)->volume();
            }
            else if(_solids->at(i)->numberOfChild() > 0){ //composite has child
                count = count + _solids->at(i)->volumn_composite_has_child(_solids->at(i));
            }
        }
        
        return count;
    }

private:
    std::vector<Solid*> * _solids;
};

#endif