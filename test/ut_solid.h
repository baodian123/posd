#ifndef UT_SOLID
#define UT_SOLID

#include <gtest/gtest.h>
#include "../src/cone.h"
#include "../src/square_cylinder.h"
#include "../src/triangular_pyramid.h"
#include "../src/complex_solids.h"
#include <math.h>
#include <vector>

TEST (SolidTest, TriangularPyramidCalculate){
  TriangularPyramid* triangularPyramid = new TriangularPyramid(0.0, 0.0, 1.0, 3.0, 3.0, 0.0, 4.0);
  ASSERT_NEAR(triangularPyramid->bottomArea(), 4.5, 0.001);
  ASSERT_NEAR(triangularPyramid->volume(), 6, 0.001);
}

TEST (SolidTest, ConeCalculate)
{
  Cone* cone = new Cone(0.0, 0.0, 1.0, 0.0, 3.0);
  ASSERT_EQ(cone->bottomArea(), M_PI);
  ASSERT_EQ(cone->volume(), M_PI);
}

TEST (SolidTest, SquareCylinderCaculate)
{
  SquareCylinder* squareCylinder = new SquareCylinder(2.0, 2.0);
  ASSERT_EQ(squareCylinder->bottomArea(), 4.0);
  ASSERT_EQ(squareCylinder->volume(), 8.0);
}

TEST (SolidTest, ComplexSolidsTest)
{
  // 2 points
  // Test numberOfChild of ComplexSolids
  Cone* cone = new Cone(0.0, 0.0, 1.0, 0.0, 3.0);
  SquareCylinder* squareCylinder = new SquareCylinder(2.0, 2.0);

  std::vector<Solid*> solids;
  solids.push_back(cone);
  solids.push_back(squareCylinder);
  
  Solid* m_solid = new ComplexSolids(&solids);
  int num = m_solid->numberOfChild();
  ASSERT_EQ(num, 2);
}

TEST (SolidTest, ComplexSolidsCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of ComplexSolids
  Cone* cone = new Cone(0.0, 0.0, 1.0, 0.0, 3.0);
  SquareCylinder* squareCylinder = new SquareCylinder(2.0, 2.0);

  std::vector<Solid*> solids;
  solids.push_back(cone);
  solids.push_back(squareCylinder);
  
  Solid* m_solid = new ComplexSolids(&solids);
  ASSERT_EQ(m_solid->bottomArea(), cone->bottomArea() + squareCylinder->bottomArea());
  ASSERT_EQ(m_solid->volume(), cone->volume() + squareCylinder->volume());
}


TEST (SolidTest, findBySolid){
  // 5 points
  // Test find() method of cone and TriangularPyramid and SquareCylinder
  Cone* cone = new Cone(0.0, 0.0, 1.0, 0.0, 3.0);
  std::vector<Solid*> s = cone->find(0, 1000000, 0, 1000000);
  ASSERT_EQ(1, s.size());
}

TEST (SolidTest, findByComplextSolids){
  // 5 points
  // Test find() method of ComplexSolids
  Cone* cone = new Cone(0.0, 0.0, 1.0, 0.0, 3.0);
  SquareCylinder* squareCylinder = new SquareCylinder(2.0, 2.0);
  TriangularPyramid* triangularPyramid = new TriangularPyramid(0.0, 0.0, 1.0, 3.0, 3.0, 0.0, 4.0);

  Cone* cone_s = new Cone(0.0, 0.0, 1.0, 0.0, 3.0);
  SquareCylinder* squareCylinder_s = new SquareCylinder(2.0, 2.0);
  TriangularPyramid* triangularPyramid_s = new TriangularPyramid(0.0, 0.0, 1.0, 3.0, 3.0, 0.0, 4.0);
  std::vector<Solid*> solids_s;
  solids_s.push_back(cone_s);
  solids_s.push_back(squareCylinder_s);
  solids_s.push_back(triangularPyramid_s);
  Solid* m_solid_s = new ComplexSolids(&solids_s);

  std::vector<Solid*> solids;
  solids.push_back(cone);
  solids.push_back(squareCylinder);
  solids.push_back(triangularPyramid);
  
  Solid* m_solid = new ComplexSolids(&solids);
  m_solid->add(m_solid_s);
  std::vector<Solid*> s = m_solid->find(0, 1000000.0, 0, 1000000.0);
  ASSERT_EQ(s.size(), 6);
}
#endif