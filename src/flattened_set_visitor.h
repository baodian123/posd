#ifndef FLATTENED_SET_VISITOR_H
#define FLATTENED_SET_VISITOR_H

#include "visitor.h"
#include <vector>
class Element;

class FlattenedSetVisitor : public Visitor{
    public:
        FlattenedSetVisitor(){}
        void visitInteger(Integer* i);
        void visitSet(Set* i);
        Element* getResult();
        void clearV();
    
    private:
        std::vector<Element*> visitor_element;
};

#endif