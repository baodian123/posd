#ifndef ELEMENT_H
#define ELEMENT_H

#include<string>
#include "iterator.h"
#include "visitor.h"

class Element{
public:
    Element(){
    }

    virtual void add(Element * s) = 0;

    virtual int size()=0;

    virtual std::string toString() = 0;

    virtual Iterator * createIterator() = 0;

    virtual void setOperator(char ope) = 0;

    virtual void accept(Visitor * fsv) = 0;

    virtual int cast() = 0;

    virtual double getValue() = 0;

    virtual void acceptjump(Visitor * fsv) = 0;

};

#endif