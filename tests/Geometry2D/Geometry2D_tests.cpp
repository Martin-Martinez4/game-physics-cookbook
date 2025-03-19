#include <gtest/gtest.h>
#include "Geometry2D.h"
#include <vector>

// Tests

/*
Test Vertices are made correctly
  - Line2D
  - Circle
  - Rectangle2D
  - OrientedRectangle
*/
TEST(Geometry2D, Geometry2DVertices){

  /* --Line-- */
  struct lineVertTest{
    vec2 start;
    vec2 end;
    std::vector<vec2> want;
  };

   std::vector<lineVertTest> lineVertTests = {
    {
      vec2(0,0),
      vec2(1,1),
      std::vector<vec2> {vec2(0,0), vec2(1,1)}
    },
    {
      vec2(-1,10),
      vec2(10,10),
      std::vector<vec2> {vec2(-1,10), vec2(10,10)}
    },
    {
      vec2(-5.5f, 1.5f),
      vec2(10,10),
      std::vector<vec2> {vec2(-5.5f, 1.5f), vec2(10,10)}
    }
  };

  for(int i = 0; i < lineVertTests.size(); ++i){
    lineVertTest t = lineVertTests[i];
    Line2D l(t.start, t.end);

    EXPECT_EQ(l.vertices[0], t.want[0]);
    EXPECT_EQ(l.vertices[1], t.want[1]);
  }

  /* --Circle-- */
  struct circleVertTest{
    vec2 center;
    std::vector<vec2> want;
  };

   std::vector<circleVertTest> circleVertTests = {
    {
      vec2(0,0),
      std::vector<vec2> {vec2(0,0)}
    },
    {
      vec2(10,10),
      std::vector<vec2> {vec2(10,10)}
    },
    {
      vec2(-5.5f, 1.5f),
      std::vector<vec2> {vec2(-5.5f, 1.5f)}
    }
  };

  for(int i = 0; i < circleVertTests.size(); ++i){
    circleVertTest t = circleVertTests[i];
    Circle c(t.center, 1);

    EXPECT_EQ(c.vertices[0], t.want[0]);
  }

   /* --Rectangle-- */
  struct rectangleVertTest{
    vec2 position;
    vec2 size;
    std::vector<vec2> want;
  };

   std::vector<rectangleVertTest> rectangleVertTests = {
    {
      vec2(0,0),
      vec2(2,4),
      std::vector<vec2> {vec2(-1,2), vec2(1,2), vec2(1,-2), vec2(-1,-2),}
    },
    {
      vec2(2,1),
      vec2(4,2),
      std::vector<vec2> {vec2(0,2), vec2(4,2), vec2(4,0), vec2(0,0),}
    },
    {
      vec2(-3.5,-3.5),
      vec2(7,7),
      std::vector<vec2> {vec2(-7,0), vec2(0,0), vec2(0,-7), vec2(-7,-7),}
    },
  };

  for(int i = 0; i < rectangleVertTests.size(); ++i){
    rectangleVertTest t = rectangleVertTests[i];
    Rectangle2D r(t.position, t.size);

    EXPECT_EQ(r.vertices.size(), t.want.size());

    for(int j = 0; j < t.want.size(); ++j){
      EXPECT_EQ(r.vertices[j], t.want[j]);
    }
  }

  /* --Oriented Rectangle-- */
  struct orientedRectangleVertTest{
    vec2 position;
    vec2 halfExtents;
    float rotation;
    std::vector<vec2> want;
  };

   std::vector<orientedRectangleVertTest> orientedRectangleVertTests = {
    {
      vec2(0,0),
      vec2(1,2),
      90,
      std::vector<vec2> {vec2(-2,-1), vec2(-2,1), vec2(2,1), vec2(2, -1),}
    },
    {
      vec2(0,0),
      vec2(1,2),
      45,
      std::vector<vec2> {vec2(-2.12132,0.707106), vec2(-0.707107,2.12132), vec2(2.12132,-0.707107), vec2(.707107,-2.12132),}
    },
    {
      vec2(0,0),
      vec2(1,2),
      -45,
      std::vector<vec2> {vec2(.707107,2.12132), vec2(2.12132,0.707107), vec2(-0.707107,-2.12132), vec2(-2.12132,-0.707106)}
    },
  };

  for(int i = 0; i < orientedRectangleVertTests.size(); ++i){
    orientedRectangleVertTest t = orientedRectangleVertTests[i];
    OrientedRectangle r(t.position, t.halfExtents, t.rotation);

    EXPECT_EQ(r.vertices.size(), t.want.size());

    for(int j = 0; j < t.want.size(); ++j){
      EXPECT_EQ(r.vertices[j], t.want[j]);
    }
  }

}

/*
Test Point on/in
  - PointOnLine
  - PointInCircle
  - PointInRectangle
  - PointInOrientedRectangle
*/

/*
Test Line Intersection
  - LineCircle
  - LineRectangle
  - LineOrientedRectangle
*/

/*
Test Circle Intersection
  - CircleCircle
  - CircleRectangle
  - CircleOrientedRectangle
*/
TEST(Geometry2D, CircleIntersection){
  struct circleCircleTest{
    Circle c1;
    Circle c2;
    bool want;
  };
}

/*
Test Rectangle Intersection
  - RectangleRectangleSAT
  - RectangleOrientedRectangle
  - OrientedRectangleOrientedRectangle
*/

/* 
Test SATCollision
  - SATCollision; copy and paste other tests
*/

