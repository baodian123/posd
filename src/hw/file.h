#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include "null_iterator.h"
#include "node.h"

class File: public Node {
public:
  File(std::string path): Node(path) {
      m_path = path;
      DIR* dir = opendir(path.c_str());
      if(dir != NULL){
          std::string s = "It is not File!";
          closedir(dir);
          throw s;
      }
      FILE* fp = fopen(path.c_str(), "r");
      if(fp == NULL){
          std::string s = "Node is not exist!";
          throw s;
      }
      else fclose(fp);
  }

  std::string name(){
    return getFileLastName(m_path);
  }

  std::string findNode(std::string name){
    std::string lastName = getFileLastName(m_path);
    if(lastName == name) return lastName;
    else{
        std::string s;
        return s;
    }
  }

  void accept(Visitor* visitor){
      visitor->visitFile(this);
  }

  Iterator *createIterator(){
    return new NullIterator();
  }

  std::string listNode(){
    std::string s = "Not a directory";
    throw s;
  }

private:
  std::string m_path;
};

#endif
