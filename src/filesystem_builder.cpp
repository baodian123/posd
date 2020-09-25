#include "filesystem_builder.h"
#include "folder.h"
#include "file.h"
#include "link.h"
#include <sys/stat.h>
#include <cstring>

FileSystemBuilder* FileSystemBuilder::singleton = nullptr;

FileSystemBuilder* FileSystemBuilder::instance(){
    if (singleton == nullptr){
        singleton = new FileSystemBuilder();
    }
    return singleton;
}

Node* FileSystemBuilder::getRoot(){
    return this->_root;
}

void FileSystemBuilder::build(std::string path){
    DIR * root = opendir(path.c_str());
    if(root != nullptr){
        _root = new Folder(path);
        struct dirent * dp;
        while((dp = readdir(root)) != NULL){
            if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) continue;
            if(dp->d_type == DT_REG){
                Node * n = new File(std::string(path) + "/" + std::string(dp->d_name));
                _root->addChild(n);
            }
            else if(dp->d_type == DT_DIR){
                Node * n = new Folder(std::string(path) + "/" + std::string(dp->d_name));
                FileSystemBuilder* fb = new FileSystemBuilder();
                fb->build(std::string(path) + "/" + std::string(dp->d_name));
                _root->addChild(fb->getRoot());
            }
            else if(dp->d_type == DT_LNK){
                Node * n = new Link(std::string(path) + "/" + std::string(dp->d_name), nullptr);
                _root->addChild(n);
            }
        }
        closedir(root);
    }
    else{
        FILE* fp = fopen(path.c_str(), "r");
        if(fp == nullptr) throw std::string("not a folder and a file");
        else _root = new File(path);
        fclose(fp);
    }
}