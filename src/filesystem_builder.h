#ifndef FILESYSTEM_BUILDER_H
#define FILESYSTEM_BUILDER_H

#include <string>
#include "node.h"

class FileSystemBuilder{
    protected:
        FileSystemBuilder(){}
    public:
        static FileSystemBuilder * instance();
        void build(std::string path);
        Node * getRoot();
    
    private:
        Node* _root;
        static FileSystemBuilder* singleton;
};

#endif