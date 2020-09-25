#ifndef INTEGER_H
#define INTEGER_H

#include "element.h"
#include "iterator.h"
#include "null_iterator.h"

class Integer : public Element{
public:
    Integer(int value): m_value(value){}

    void add(Element * s){
        throw std::string("It's an integer!");
    }

    int size(){
        return 1;
    }

    std::string toString(){
        std::string s = std::to_string(m_value);
        return s;
    }

    Iterator * createIterator(){
        return new NullIterator();
    }

    void setOperator(char ope){
        throw std::string("Cannot set operator on it!");
    }

    void accept(Visitor * fsv){
        fsv->visitInteger(this);
    }

    void acceptjump(Visitor * fsv){
        fsv->visitInteger(this);
    }

    int cast(){
        return 3;
    }

    double getValue(){
        return m_value;
    }

private:
    int m_value;
};

#endif