#ifndef __UT_SORT__
#define __UT_SORT__

#include "../src/shape.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/circular_sector.h"
#include "../src/sort.h"
#include "../src/terminal.h"
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

TEST (ShapeTest, Sortbydescending){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;  
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    sort->sortArea(areaDescendingComparison);

    ASSERT_EQ(shapes.at(0), ellipse);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), circularSector);
}

TEST (ShapeTest, Sortbyobject){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;  
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    AscendingComparison ascendingComparison("area");
    sort->sortArea(ascendingComparison);

    ASSERT_EQ(shapes.at(0), circularSector);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), ellipse);
}

TEST (ShapeTest, Sortbyfunction){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    sort->sortArea(areaAscendingComparison);

    ASSERT_EQ(shapes.at(0), circularSector);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), ellipse);
}

TEST (ShapeTest, Sortbylambda){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;  
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    sort->sortArea([](Shape* s1, Shape* s2){ return s1->area() < s2->area(); });

    ASSERT_EQ(shapes.at(0), circularSector);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), ellipse);
}

TEST (ShapeTest, Quicksortbyobject){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;  
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    AscendingComparison ascendingComparison("area");
    sort->quickSort(ascendingComparison);

    ASSERT_EQ(shapes.at(0), circularSector);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), ellipse);
}

TEST (ShapeTest, Quicksortbyfunction){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;  
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    sort->quickSort(areaDescendingComparison);

    ASSERT_EQ(shapes.at(0), ellipse);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), circularSector);
}

TEST (ShapeTest, Quicksortbylambda){
    CircularSector *circularSector = new CircularSector(1, 90);
    Ellipse *ellipse = new Ellipse(20, 10);
    Triangle *triangle = new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);

    vector<Shape*> shapes;
    shapes.push_back(ellipse);
    shapes.push_back(triangle);
    shapes.push_back(circularSector);
    Sort* sort = new Sort(&shapes);
    sort->quickSort([](Shape* s1, Shape* s2){ return s1->area() < s2->area(); });

    ASSERT_EQ(shapes.at(0), circularSector);
    ASSERT_EQ(shapes.at(1), triangle);
    ASSERT_EQ(shapes.at(2), ellipse);
}

TEST (ShapeTest, CircularSector)
{
  CircularSector circularSector(1, 90);
  ASSERT_EQ(M_PI * M_PI * 0.25 * 0.25 + (0.5 * M_PI + 2) * (0.5 * M_PI + 2), circularSector.sumOfSquares());
}

TEST (ShapeTest, Ellipse)
{
  Ellipse ellipse(20, 10);
  ASSERT_NEAR(M_PI * M_PI * 40000.0 + (20 * M_PI + 40) * (20 * M_PI + 40), ellipse.sumOfSquares(), 1);
}

TEST (ShapeTest, Triangle)
{
  Triangle triangle(0.0, 0.0, 3.0, 0.0, 0.0, 3.0);
  ASSERT_NEAR((6.0 + 3.0 * sqrt(2)) * (6.0 + 3.0 * sqrt(2)) + 20.25, triangle.sumOfSquares(), 0.01);
}

TEST(TerminalTest, teminal_area)
{
  Terminal* test = new Terminal("Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc");
  string str = test->showResult();
  ASSERT_EQ(str, "[6.000000, 22.340214, 94.247780]");
}

TEST(TerminalTest, teminal_sumofsquares)
{
  Terminal* test = new Terminal("Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) sumOfSquares dec");
  string str = test->showResult();
  ASSERT_EQ(str, "[10136.931813, 964.999720, 210.533231]");
}

TEST(TerminalTest, teminal_perimeter)
{
  Terminal* test = new Terminal("Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) perimeter dec");
  string str = test->showResult();
  ASSERT_EQ(str, "[35.415927, 21.585054, 13.211103]");
}

TEST(TerminalTest, teminal_special_characters)
{
  Terminal* test = new Terminal("Ellipse%% (6,5) Triangle(3,0,0,2,-3,0) CircularSector (8,40) %!)(= perimeter inc");
  string str = test->showResult();
  ASSERT_EQ(str, "[21.585054]");
}

TEST(TerminalTest, teminal_throw_string)
{
  try{
    Terminal *test = new Terminal("Ellipse%% (6,5) Triangle(3,0,0,2,-3,0) CircularSector (8,40) %!)(= inc");
    string str = test->showResult();
    FAIL();
  }
  catch(std::string& e){
    ASSERT_EQ(e, "Unuseful User Input!");
  }
  catch(...){
    cout << "Unknown Exception" << endl;
  }
}

#endif