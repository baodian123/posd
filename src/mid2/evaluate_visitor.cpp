#include "evaluate_visitor.h"
#include "set.h"
#include "integer.h"
#include "iterator.h"
#include <iostream>

void EvaluateVisitor::visitSet(Set* set){
    double setResult = 0;
    if(set->size() != 0) setResult = set->getValue();
    // Iterator* iter = set->createIterator();
    // iter->first();
    // while(!iter->isDone()){
    //     setResult += iter->currentItem()->getValue();
    //     iter->currentItem()->acceptjump(this);
    //     iter->next();
    // }
    this->result = setResult;
}

void EvaluateVisitor::visitInteger(Integer* i){
    this->result = i->getValue();
}

double EvaluateVisitor::getResult(){
    return this->result;
}