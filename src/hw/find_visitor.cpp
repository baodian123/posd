#include "find_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node.h"
#include "iterator.h"

void FindVisitor::visitFile(File * file){
    this->m_result = "";
    if(file->getFileLastName(file->getFileName()) == this->m_name){
        m_result = file->getFileLastName(file->getFileName());
    }
}

void FindVisitor::visitFolder(Folder * folder){
    this->m_result = "";
    if(m_name.find(".") != std::string::npos){  //find file
        Iterator* iter = folder->createIterator();
        iter->first();
        if(iter->isDone()) return;
        else{
            while(!iter->isDone()){
                if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()) == m_name){
                    m_result = m_result + iter->currentItem()->getFileName() + "*";
                }
                else if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()).find(".") == std::string::npos){
                    m_result = m_result + iter->currentItem()->fileFindNode(iter->currentItem(), m_name);
                }
                iter->next();
            }
        }
    }
    if(m_name.find(".") == std::string::npos){  //find folder
        Iterator* iter = folder->createIterator();
        iter->first();
        if(iter->isDone()) return;
        else{
            while(!iter->isDone()){
                if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()) == m_name){
                    m_result = m_result + iter->currentItem()->getFileName() + "*" + iter->currentItem()->folderFindNode(iter->currentItem(), m_name);
                }
                else if(iter->currentItem()->getFileLastName(iter->currentItem()->getFileName()).find(".") == std::string::npos){
                    m_result = m_result + iter->currentItem()->folderFindNode(iter->currentItem(), m_name);
                }
                iter->next();
            }
        }
    }

    std::string final_path = "";
    std::string delimiter = "*";
    size_t pos = 0;
    std::string token;
    while ((pos = m_result.find(delimiter)) != std::string::npos) {
        token = m_result.substr(0, pos);
        final_path = final_path + "." + token.substr(folder->getFileName().size(), token.size());
        m_result.erase(0, pos + delimiter.length());
        if(m_result.find(delimiter) != std::string::npos) final_path += "\n";
    }
    final_path += m_result.substr(0, m_result.size()-1);
    m_result = final_path;
}

void FindVisitor::visitLink(Link * link){
    this->m_result = "";
    if(link->getFileLastName(link->getFileName()) == this->m_name){
        m_result = link->getFileLastName(link->getFileName());
    }
}

std::string FindVisitor::findResult(){
    return m_result;
}