#include "flattened_set_visitor.h"
#include "set.h"
#include "integer.h"
#include "iterator.h"
#include <iostream>

void FlattenedSetVisitor::visitSet(Set* set){
    Iterator* iter = set->createIterator();
    iter->first();
    while(!iter->isDone()){
        iter->currentItem()->acceptjump(this);
        iter->next();
    }
}

void FlattenedSetVisitor::visitInteger(Integer* i){
    this->visitor_element.push_back(i);
}

Element* FlattenedSetVisitor::getResult(){
    if(this->visitor_element.size() == 1){
        return visitor_element.at(0);
    }

    Element* set = new Set();
    for(int i=0; i<this->visitor_element.size(); i++){
        set->add(this->visitor_element.at(i));
    }
    return set;
}

void FlattenedSetVisitor::clearV(){
    this->visitor_element.clear();
}