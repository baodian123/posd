#ifndef NULL_ITEREATOR_H
#define NULL_ITEREATOR_H
#include "iterator.h"
#include <string>

class Element;
class NullIterator:public Iterator
{
  public:
    NullIterator(){}
    void first(){
      std::string s = "No child member!";
      throw s;
    }
    Element* currentItem(){
      std::string s = "No child member!";
      throw s;
    }
    void next() {
      std::string s = "No child member!";
      throw s;
    }
    bool isDone(){
      return true;
    }
};

#endif