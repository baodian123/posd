#ifndef LINK_H
#define LINK_H

#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include "node.h"
#include "null_iterator.h"

class Link : public Node{
public:
  Link(std::string path, Node * node): Node(path), m_node(node){
      m_path = path;
      struct stat buf;
      int status = lstat(path.c_str(), &buf);
      if(!S_ISLNK(buf.st_mode) || status != 0){
          std::string s = "It is not Link!";
          throw s;
      }
  } // You should check path if it is not a link that you should throw string "It is not Link!"

  void accept(Visitor* visitor){
      visitor->visitLink(this);
  } // aceep visitor

  void addLink(Node * node){
      m_node = node;
  } // add symbolic link

  Node * getSource(){
      return m_node;
  } // return node that the link point to!

  Iterator* createIterator(){
      return new NullIterator();
  } // return null Iterator

private:
    std::string m_path;
    Node* m_node;
};

#endif