#ifndef __SORT__
#define __SORT__

#include <iostream>
#include "shape.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <typename partition_f>
vector<Shape*>::iterator partition(vector<Shape*>::iterator start, vector<Shape*>::iterator end, partition_f f) 
{ 
    vector<Shape*>::iterator partition_index = start;
  
    for(auto compare=start; compare!=end; compare++){ 
        if(f(*compare, *end)){
            iter_swap(compare, partition_index);
            partition_index++;
        }
    }
    iter_swap(partition_index, end);
    return partition_index;
}

template <typename quicksort>
void QSort(vector<Shape*>::iterator start, vector<Shape*>::iterator end, quicksort f)
{
    int distance = std::distance(start, end);
    if(distance <= 1) return;
    auto partition_index = partition(start, end, f);
    QSort(start, partition_index - 1, f);
    QSort(partition_index, end, f);
}

class Sort{
    public:
      Sort(std::vector<Shape*>* v): _v(v){}
      
      template <typename f_area>
      void sortArea(f_area f){
          std::sort(_v->begin(), _v->end(), f);
      }

      template <typename f_perimeter>
      void sortPerimeter(f_perimeter f){
          std::sort(_v->begin(), _v->end(), f);
      }
      
      template <typename f_sumofsquares>
      void sortSumOfSquares(f_sumofsquares f){
          std::sort(_v->begin(), _v->end(), f);
      }
      
      template <typename f_quicksort>
      void quickSort(f_quicksort f){
          QSort(_v->begin(), _v->end()-1, f);
      }

    private:
      std::vector<Shape*>* _v;
};

class AscendingComparison{
    public:
        AscendingComparison(string compare_str): _compare_str(compare_str){}
        bool operator ()(Shape* shape1, Shape* shape2)
 	    {
            if(_compare_str == "area")
 	 	        return shape1->area() < shape2->area();
            if(_compare_str == "perimeter")
                return shape1->perimeter() < shape2->perimeter();
            if(_compare_str == "sumOfSquares")
                return shape1->sumOfSquares() < shape2->sumOfSquares();
	    }

    private:
        string _compare_str;
};

class DescendingComparison{
    public:
        DescendingComparison(string compare_str){}
        bool operator ()(Shape* shape1, Shape* shape2)
 	    {
            if(_compare_str.compare("area"))
 	 	        return shape1->area() > shape2->area();
            if(_compare_str.compare("perimeter"))
                return shape1->perimeter() > shape2->perimeter();
            if(_compare_str.compare("sumOfSquares"))
                return shape1->sumOfSquares() > shape2->sumOfSquares();
	    }

    private:
        string _compare_str;
};

// implement following call back function
bool areaAscendingComparison(Shape *a, Shape *b){
    return a->area() < b->area();
}

bool areaDescendingComparison(Shape *a, Shape *b){
    return a->area() > b->area();
}

#endif