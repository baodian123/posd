#ifndef SET_H
#define SET_H

#include "element.h"
#include "iterator.h"
#include <iostream>
#include <vector>
#include "flattened_set_visitor.h"

class Set : public Element{
    class SetIterator: public Iterator{
        public:
            SetIterator(Set* set): m_set(set){}
            void first(){
                current = m_set->v.begin();
            }

            Element* currentItem(){
                if(current == m_set->v.end()){
                    std::string s = "No current item!";
                    throw s;
                }
                else return *current;
            }

            void next(){
                if(current == m_set->v.end()){
                    std::string s = "Moving past the end!";
                    throw s;
                }
                else current++;
            }

            bool isDone(){
                return current == m_set->v.end();
            }

        private:
            Set* m_set;
            std::vector<Element*>::iterator current;
    };
public:
    Set(){
        m_ope = '+';
    }

    void add(Element * element){
        v.push_back(element);
    }

    int size(){
        return v.size();
    }

    std::string toString(){
        std::string s = "";
        s += "{";
        bool isbegin = true;
        for(int i=0; i<v.size(); i++){
            if(v.at(i)->cast() == 3){  //is integer
                if(isbegin){
                    s += v.at(i)->toString();
                    isbegin = false;
                }
                else s = s + "," + v.at(i)->toString();
            }
            if(v.at(i)->cast() == 6){  //is set
                if(isbegin){
                    s += v.at(i)->toString();
                    isbegin = false;
                }
                else s = s + "," + v.at(i)->toString();
            }
        }
        s += "}";
        return s;
    }

    Iterator * createIterator(){
        return new SetIterator(this);
    }

    void setOperator(char ope){
        if(ope != '+' && ope != '-' && ope != '*' && ope != '/'){
            std::string s = "Invalid operator!";
            throw s;
        }
        m_ope = ope;
    }

    void accept(Visitor * fsv){
        fsv->clearV();
        fsv->visitSet(this);
    }

    void acceptjump(Visitor * fsv){
        fsv->visitSet(this);
    }

    int cast(){
        return 6;
    }

    double getValue(){
        if(v.size() == 0) return 0;
        double result = v.at(0)->getValue();
        if(m_ope == '+'){
            for(int i=1; i<v.size(); i++){
                result = result + v.at(i)->getValue();
            }
        }

        else if(m_ope == '-'){
            for(int i=1; i<v.size(); i++){
                result = result - v.at(i)->getValue();
            }
        }

        else if(m_ope == '*'){
            for(int i=1; i<v.size(); i++){
                result = result * v.at(i)->getValue();
            }
        }
        
        else if(m_ope == '/'){
            for(int i=1; i<v.size(); i++){
                if(v.at(i)->getValue() == 0){
                    std::string s = "Divide by zero!";
                    throw s;
                }
                result = result / v.at(i)->getValue();
            }
        }

        return result;
    }

private:
    char m_ope;
    std::vector<Element*> v;
};

#endif