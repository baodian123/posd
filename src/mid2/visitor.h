#ifndef VISITOR_H
#define VISITOR_H

class Integer;
class Set;

class Visitor{
    public:
        virtual void visitInteger(Integer* i) = 0;
        virtual void visitSet(Set* i) = 0;
        virtual void clearV(){}
};


#endif