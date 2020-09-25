#ifndef FOLDER_H
#define FOLDER_H
 
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <map>
#include <algorithm>
#include "node.h"
 
using namespace std;
 
class Folder: public Node {
    class FolderIterator : public Iterator
    {
    public:
    FolderIterator(Folder * f): _f(f){}
        void first()
        {
            // initialization
            _current = _f->_m.begin();
        }
        Node* currentItem()
        {
            // if iterator is to the end that it should throw string "No current item!"
            // if iterator is not to the end that it should return current node
            if(_current == _f->_m.end()){
                std::string s = "No current item!";
                throw s;
            }
            else return _current->second;
        }
        void next()
        {
            // if iterator is to the end that it should throw string "Moving past the end!"
            // if iterator is not to the end that it should add 1
            if(_current == _f->_m.end()){
                std::string s = "Moving past the end!";
                throw s;
            }
            else _current++;
        }
        bool isDone()
        {
            return _current == _f->_m.end();
        }
    private:
        Folder * _f;
        std::map<string, Node*>::iterator _current;
    };

public:
  Folder(std::string path): Node(path) {
      m_path = path;
      FILE* fp = fopen(path.c_str(), "r+");
      if(fp != NULL){
        std::string s = "It is not Folder!";
        fclose(fp);
        throw s;
      }
      DIR* dir = opendir(path.c_str());
      if(dir == NULL){
        std::string s = "Node is not exist!";
        throw s;
      } 
      else closedir(dir);
  }
 
  void addChild(Node* child) {
    _m.insert(pair<std::string, Node*>(child->getFileName(), child));
  }
 
  Node* getChild(string path) {
    map<string, Node*>::iterator iter = _m.find(path);
    if(iter != _m.end()) return iter->second;
    else return nullptr;
  }

  int getChildSize(){
      return _m.size();
  }

  Iterator *createIterator() {
    return new FolderIterator(this);
  }

  std::string fileFindNode(Node* node, std::string name){
    string s = "";
    Iterator* iter = node->createIterator();
    iter->first();
    if(iter->isDone()) return s;
    else{
      while(!iter->isDone()){
        if(name == getFileLastName(iter->currentItem()->getFileName())) s = s + iter->currentItem()->getFileName() + "*";
        else if(getFileLastName(iter->currentItem()->getFileName()).find(".") == std::string::npos){
          s = s + iter->currentItem()->fileFindNode(iter->currentItem(), name);
        }
        iter->next();
      }
      return s;
    }
  }

  std::string folderFindNode(Node* node, std::string name){
    string s = "";
    Iterator* iter = node->createIterator();
    iter->first();
    if(iter->isDone()) return s;
    else{
      while(!iter->isDone()){
        if(name == getFileLastName(iter->currentItem()->getFileName())) s = s + iter->currentItem()->getFileName() + "*" + iter->currentItem()->folderFindNode(iter->currentItem(), name);
        else if(getFileLastName(iter->currentItem()->getFileName()).find(".") == std::string::npos){
          s = s + iter->currentItem()->folderFindNode(iter->currentItem(), name);
        }
        iter->next();
      }
      return s;
    }
  }

  void accept(Visitor* visitor){
    visitor->visitFolder(this);
  }
  
  // std::string name(){
  //   return getFileLastName(m_path);
  // }
 
private:
  std::string m_path;
  std::map<std::string,Node *> _m;
};
#endif