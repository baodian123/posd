#ifndef NULL_ITEREATOR_H
#define NULL_ITEREATOR_H
#include "iterator.h"
#include <string>

class Node;
class NullIterator:public Iterator
{
  public:
    void first(){
      std::string s = "no child member";
      // throw s;
    }
    Node* currentItem(){
      std::string s = "no child member";
      throw s;
    }
    void next() {
      std::string s = "no child member";
      throw s;
    }
    bool isDone(){
      return true;
    }
};

#endif
