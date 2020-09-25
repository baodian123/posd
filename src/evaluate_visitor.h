#ifndef EVALUATE_H
#define EVALUATE_H

#include "visitor.h"
#include <vector>

class Element;

class EvaluateVisitor : public Visitor{
    public:
        EvaluateVisitor(){}
        void visitInteger(Integer* i);
        void visitSet(Set* i);
        double getResult();
    
    private:
        double result;
};

#endif