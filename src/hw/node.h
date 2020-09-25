#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <iostream>
#include "iterator.h"
#include "visitor.h"

class Node {
public:
  Node(std::string path): _path(path) {
    stat(_path.c_str(), &_st);
  }

  int size() {
    return _st.st_size;
  }

  std::string getFileName(){
      return _path;
  }

  std::string getPath(){
      return _path;
  }

  virtual void addChild(Node* child) {
    throw(std::string("Invalid add!"));
  }

  virtual Node* getChild(std::string path) {
    return nullptr;
  }

  virtual int infoByte(){
    return size();
  }

  void renameNode(std::string name){
    std::string s = _path.substr(0, _path.size() - this->getFileLastName(_path).size()) + name;
    int ret = rename(_path.c_str(), s.c_str());
    if(ret == 0) _path = s;
    // else std::cout << "rename fail" << std::endl;
  }

  void setPath(std::string path){
    _path = path;
  }

  virtual void accept(Visitor* visitor){}

  virtual Iterator *createIterator() = 0;

  virtual std::string name(){}

  virtual std::string findNode(std::string name){}

  virtual std::string listNode(){}

  virtual std::string folderFindNode(Node* _v, std::string name){}

  virtual std::string fileFindNode(Node* _v, std::string name){}

  virtual int getChildSize(){
    return 0;
  }

  std::string getFileLastName(std::string name){
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    while ((pos = name.find(delimiter)) != std::string::npos) {
        token = name.substr(0, pos);
        name.erase(0, pos + delimiter.length());
    }
    return name;
  }

private:
  std::string _path;
  struct stat _st;
};

#endif