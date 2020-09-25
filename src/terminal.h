#ifndef __TERMINAL__
#define __TERMINAL__

#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include "shape.h"
#include "ellipse.h"
#include "triangle.h"
#include "circular_sector.h"
#include "terminal.h"
#include "sort.h"
using namespace std;

double rounding(double num, int index){
    bool isNegative = false;
    if(num < 0){
        isNegative = true;	
        num = -num;
    }
    if(index >= 0){
        int multiplier;
        multiplier = pow(10, index);
        num = (long int)(num * multiplier + 0.5) / (multiplier * 1.0);
    }
    if(isNegative){
        num = -num;
    }
    return num;
}

class Terminal
{
    public:
         // you can use regular expression to get useful token from "Input string"
        Terminal(string inString): _inString(inString){}

        std::string showResult(){
            regex reg("(((Ellipse )([\\(])([0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([0-9]+[\\.]?[0-9]*)([\\)]))|((Triangle )([\\(])([-]?[0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([-]?[0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([-]?[0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([-]?[0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([-]?[0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([-]?[0-9]+[\\.]?[0-9]*)([\\)]))|((CircularSector )([\\(])([0-9]+[\\.]?[0-9]*)([ ]*)(,)([ ]*)([0-9]+[\\.]?[0-9]*)([\\)])))");
            
            auto words_begin = std::sregex_iterator(_inString.begin(), _inString.end(), reg);
            auto words_end = std::sregex_iterator();
            vector<Shape*> m_vector;

            for(std::sregex_iterator i = words_begin; i != words_end; ++i){
                std::smatch match = *i;
                std::string match_str = match.str();
                if(regex_search(match_str, reg)){
                    std::smatch sm;
                    regex_match(match_str, sm, reg);
                    for(unsigned j=0; j<sm.size(); j++){
                        if(sm[j] == "Ellipse "){
                            Ellipse *ellipse = new Ellipse(stod(sm[j+2]), stod(sm[j+6]));
                            m_vector.push_back(ellipse);
                        }
                        if(sm[j] == "Triangle "){
                            Triangle *triangle = new Triangle(stod(sm[j+2]), stod(sm[j+6]), stod(sm[j+10]), stod(sm[j+14]), stod(sm[j+18]), stod(sm[j+22]));
                            m_vector.push_back(triangle);
                        }
                        if(sm[j] == "CircularSector "){
                            CircularSector *circularSector = new CircularSector(stod(sm[j+2]), stod(sm[j+6]));
                            m_vector.push_back(circularSector);
                        }
                    }
                }
            }
            
            Sort* sort = new Sort(&m_vector);
            std::stringstream buffer;
            buffer << "[" ;
            std::string uu_str = "Unuseful User Input!";

            if(_inString.find("inc") == std::string::npos && _inString.find("dec") == std::string::npos) throw uu_str;
            if(_inString.find("area") != std::string::npos){
                if(_inString.find("inc") != std::string::npos) sort->sortArea([](Shape* s1, Shape* s2){ return s1->area() < s2->area(); });
                if(_inString.find("dec") != std::string::npos) sort->sortArea([](Shape* s1, Shape* s2){ return s1->area() > s2->area(); });
                for(int index=0; index<m_vector.size()-1; index++) buffer << to_string(rounding(m_vector.at(index)->area(), 6)) << ", ";
                buffer << to_string(rounding(m_vector.at(m_vector.size()-1)->area(), 6)) << "]";
            }
            else if(_inString.find("perimeter") != std::string::npos){
                if(_inString.find("inc") != std::string::npos) sort->sortPerimeter([](Shape* s1, Shape* s2){ return s1->perimeter() < s2->perimeter(); });
                if(_inString.find("dec") != std::string::npos) sort->sortPerimeter([](Shape* s1, Shape* s2){ return s1->perimeter() > s2->perimeter(); });
                for(int index=0; index<m_vector.size()-1; index++) buffer << to_string(rounding(m_vector.at(index)->perimeter(), 6)) << ", ";
                buffer << to_string(rounding(m_vector.at(m_vector.size()-1)->perimeter(), 6)) << "]";
            }
            else if(_inString.find("sumOfSquares") != std::string::npos){
                if(_inString.find("inc") != std::string::npos) sort->sortSumOfSquares([](Shape* s1, Shape* s2){ return s1->sumOfSquares() < s2->sumOfSquares(); });
                if(_inString.find("dec") != std::string::npos) sort->sortSumOfSquares([](Shape* s1, Shape* s2){ return s1->sumOfSquares() > s2->sumOfSquares(); });
                for(int index=0; index<m_vector.size()-1; index++) buffer << to_string(rounding(m_vector.at(index)->sumOfSquares(), 6)) << ", ";
                buffer << to_string(rounding(m_vector.at(m_vector.size()-1)->sumOfSquares(), 6)) << "]";
            }
            else throw uu_str;
            
            return buffer.str();
        }

    private:
        string _inString;
};

#endif