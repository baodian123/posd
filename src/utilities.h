#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include "node.h"
#include "folder.h"
#include "file.h"

class Utilities 
{
    public:
        std::string listNode(Node* node)
        {
            // You should use iterator pattern to access node in folder!
            // You can use dynamic_cast if you need
            // If node is file that it should throw string "Not a directory"
            // This function is same as Hw4 listNode()
            File * file = dynamic_cast<File *> (node);
            if(file != nullptr){
                std::string s = "Not a directory";
                throw s;
            }
            else{
                Iterator* iter = node->createIterator();
                std::string s = "";
                iter->first();
                while(!iter->isDone()){
                    s = s + iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()) + " ";
                    iter->next();
                }
                s = s.substr(0, s.size()-1);
                return s;
            }
        }

        std::string findNode(Node* node, std::string name)
        {
            // You should use iterator pattern to access node in folder!
            // You can use dynamic_cast if you need
            // This function is same as Hw4 findNode()
            File * file = dynamic_cast<File *> (node);
            if(file != nullptr){
                std::string s = node->getFileLastName(node->getFileName());
                if(s == name) return s;
                else return "";
            }
            else{
                std::string s = "";
                if(name.find(".") != std::string::npos){  //find file
                    Iterator* iter = node->createIterator();
                    iter->first();
                    if(iter->isDone()) return s;
                    else{
                        while(!iter->isDone()){
                            if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()) == name){
                                s = s + iter->currentItem()->getFileName() + "*";
                            }
                            else if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()).find(".") == std::string::npos){
                                s = s + iter->currentItem()->fileFindNode(iter->currentItem(), name);
                            }
                            iter->next();
                        }
                    }
                }
                if(name.find(".") == std::string::npos){  //find folder
                    Iterator* iter = node->createIterator();
                    iter->first();
                    if(iter->isDone()) return s;
                    else{
                        while(!iter->isDone()){
                            if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()) == name){
                                s = s + iter->currentItem()->getFileName() + "*" + iter->currentItem()->folderFindNode(iter->currentItem(), name);
                            }
                            else if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()).find(".") == std::string::npos){
                                s = s + iter->currentItem()->folderFindNode(iter->currentItem(), name);
                            }
                            iter->next();
                        }
                    }
                }
                std::string final_path = "";
                std::string delimiter = "*";
                size_t pos = 0;
                std::string token;
                while ((pos = s.find(delimiter)) != std::string::npos) {
                    token = s.substr(0, pos);
                    final_path = final_path + "." + token.substr(node->getFileName().size(), token.size());
                    s.erase(0, pos + delimiter.length());
                    if(s.find(delimiter) != std::string::npos) final_path += "\n";
                }
                final_path += s.substr(0, s.size()-1);
                return final_path;
            }
        }
};

#endif