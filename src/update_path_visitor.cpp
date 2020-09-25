#include "file.h"
#include "folder.h"
#include "link.h"
#include "node.h"
#include "iterator.h"
#include "update_path_visitor.h"

void UpdatePathVisitor::visitFile(File * file){
    return;
}

void UpdatePathVisitor::visitFolder(Folder * folder){
    std::string s = folder->getFileName();
    Iterator* iter = folder->createIterator();
    iter->first();
    if(iter->isDone()) return;
    while(!iter->isDone()){
        std::string s = folder->getFileName() + "/" + iter->currentItem()->getFileLastName(iter->currentItem()->getFileName());
        iter->currentItem()->setPath(s);
        if(iter->currentItem()->getFileName().find(".") == std::string::npos){
            UpdatePathVisitor* upv = new UpdatePathVisitor();
            iter->currentItem()->accept(upv);
        }
        iter->next();
    }
    return;
}

void UpdatePathVisitor::visitLink(Link * link){
    return;
}