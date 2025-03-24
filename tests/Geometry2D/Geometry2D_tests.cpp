#include <gtest/gtest.h>
#include "Geometry2D.h"
#include <iostream>
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
      std::vector<vec2> {vec2(0,0), vec2(0,4), vec2(2,4), vec2(2,0),}
    },
    {
      vec2(2,1),
      vec2(4,2),
      std::vector<vec2> {vec2(2,1), vec2(2,3), vec2(6,3), vec2(6,1),}
    },
    {
      vec2(-3.5,-3.5),
      vec2(7,7),
      std::vector<vec2> {vec2(-3.5,-3.5), vec2(-3.5,3.5), vec2(3.5,3.5), vec2(3.5,-3.5),}
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
      std::vector<vec2> {vec2(-2.12132f,0.707106f), vec2(-0.707107f,2.12132f), vec2(2.12132f,-0.707107f), vec2(.707107f,-2.12132f),}
    },
    {
      vec2(0,0),
      vec2(1,2),
      -45,
      std::vector<vec2> {vec2(.707107f,2.12132f), vec2(2.12132f,0.707107f), vec2(-0.707107f,-2.12132f), vec2(-2.12132f,-0.707106f)}
    },
    {
      vec2(2, 0.5f),
      vec2(2,0.5f),
      0,
      std::vector<vec2> {vec2(0,1), vec2(4, 1), vec2(4, 0), vec2(0,0)}
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

  std::vector<circleCircleTest> circleCircleTests = {
    {
      Circle(vec2(), 2),
      Circle(vec2(1,1), 1),
      true
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(2,2), 1),
      true
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(1,1.5), 1),
      true
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(2,3), 1),
      false
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(3,1), 1),
      false
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(3,1), 1.5),
      true
    },

  };

  for(int i = 0; i < circleCircleTests.size(); ++i){
    circleCircleTest t = circleCircleTests[i];
    
    EXPECT_EQ(CircleCircle(t.c1, t.c2), t.want);
  }

  struct circleRectangleTest{
    Circle c1;
    Rectangle2D r1;
    bool want;
  };

  std::vector<circleRectangleTest> circleRectangleTests = {
    {
      Circle(vec2(), 1),
      Rectangle2D(vec2(1,1), vec2(1,1)),
      false
    },
    {
      Circle(vec2(0,2), 2),
      Rectangle2D(vec2(.75,0.5), vec2(4,1)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(2,0.5), vec2(4, 0.95f)),
      false
    },
    {
      Circle(vec2(0,3), 1),
      Rectangle2D(vec2(-2.05, 3.5), vec2(2, 1.f)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(1,1), vec2(1,.5f)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(.5f,.75f), vec2(1.f,1.f)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(.5f,.75f), vec2(1.f,0.5f)),
      true
    },
    {
      Circle(vec2(-2,-2.15), 2),
      Rectangle2D(vec2(0, 1.25f), vec2(2.f,1.f)),
      false
    },
    
  };

  for(int i = 0; i < circleRectangleTests.size(); ++i){
    circleRectangleTest t = circleRectangleTests[i];
    
    EXPECT_EQ(CircleRectangle(t.c1, t.r1), t.want) << i;
  }

  struct circleOrientedRectangleTest{
    Circle c1;
    OrientedRectangle r1;
    bool want;
  };

  std::vector<circleOrientedRectangleTest> circleOrientedRectangleTests = {
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(1,1), vec2(.5,.5), 0),
      true
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(2,1), vec2(2,1.f), 0),
      true
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(2,0.5), vec2(2, 0.95f *.5f), 0),
      false
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(.5f,.5f), vec2(0.5f,0.25f), 0),
      false
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(.5f,.70f), vec2(0.5f,0.25f), 0),
      false
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(.5f,.75f), vec2(.5f,.5f), 0),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), 0),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), 90),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), 45),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), -45),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), -30),
      true
    },
    {
      Circle(vec2(-1,-1), 1),
      OrientedRectangle(vec2(-.5, 1.5f), vec2(2.f, 0.5f), -30),
      false
    },
    {
      Circle(vec2(-1,-1), 1),
      OrientedRectangle(vec2(-.5, -1.5f), vec2(2.f, 0.5f), -30),
      true
    },
    {
      Circle(vec2(-1,-1), 1),
      OrientedRectangle(vec2(-.5, -1.5f), vec2(2.25f, 1.f), -30),
      true
    },
    {
      Circle(vec2(-2,-2.15), 2),
      OrientedRectangle(vec2(0, 1.25f), vec2(2.f,1.f), 0),
      false
    },
  };

  for(int i = 0; i < circleOrientedRectangleTests.size(); ++i){
    circleOrientedRectangleTest t = circleOrientedRectangleTests[i];
    
    EXPECT_EQ(CircleOrientedRectangle(t.c1, t.r1), t.want) << i;
  }
}

/*
Test Rectangle Intersection
  - RectangleRectangle
  - RectangleOrientedRectangle
  - OrientedRectangleOrientedRectangle
*/
TEST(Geometry2D, RectangleRectangleIntersect){
  struct rectangleRectangleTest{
    Rectangle2D c1;
    Rectangle2D c2;
    bool want;
  };

  std::vector<rectangleRectangleTest> rectangleRectangleTests = {
    {
      Rectangle2D(vec2(2, 0.5f), vec2(4, 1)),
      Rectangle2D(vec2(1.5, 0.5f), vec2(1.f, 1.f)),
      true
    },
    {
      Rectangle2D(vec2(2, 1.5f), vec2(4, 1)),
      Rectangle2D(vec2(2, -0.5f), vec2(2.f, 1.f)),
      false
    },
    {
      Rectangle2D(vec2(-4.5, 3.f), vec2(3, 2)),
      Rectangle2D(vec2(-2.75, 1.75f), vec2(1.5f, 1.5f)),
      true
    },
    
  };

  for(int i = 0; i < rectangleRectangleTests.size(); ++i){
    rectangleRectangleTest t = rectangleRectangleTests[i];
    
    EXPECT_EQ(RectangleRectangle(t.c1, t.c2), t.want) << i;
  }
}

  // Rectangle OrientedRectangle
  TEST(Geometry2D, RectangleOrientedRectangleIntersect){
    struct rectangleRectangleTest{
      Rectangle2D r1;
      OrientedRectangle r2;
      bool want;
    };
  
    std::vector<rectangleRectangleTest> rectangleRectangleTests = {
      {
        Rectangle2D(vec2(2, 0.5f), vec2(4, 1)),
        OrientedRectangle(vec2(1.5, 0.5f), vec2(1.f, 1.f),0),
        true
      },
      {
        Rectangle2D(vec2(2, 1.5f), vec2(4, 1)),
        OrientedRectangle(vec2(2, -0.5f), vec2(2.f, 1.f),0),
        false
      },
      {
        Rectangle2D(vec2(-4.5, 3.f), vec2(3, 2)),
        OrientedRectangle(vec2(-2.75, 1.75f), vec2(1.5f, 1.5f),0),
        true
      },
      
    };
  
    for(int i = 0; i < rectangleRectangleTests.size(); ++i){
      rectangleRectangleTest t = rectangleRectangleTests[i];
      
      EXPECT_EQ(RectangleOrientedRectangle(t.r1, t.r2), t.want) << i;
    }
  }

  // Oriented Rectangle Oriented Rectangle
  TEST(Geometry2D, OrientedRectangleOrientedRectangleIntersect){
    struct rectangleRectangleTest{
      OrientedRectangle r1;
      OrientedRectangle r2;
      bool want;
    };
  
    std::vector<rectangleRectangleTest> rectangleRectangleTests = {
      {
        OrientedRectangle(vec2(2, 0.5f), vec2(4, 1), 0),
        OrientedRectangle(vec2(1.5, 0.5f), vec2(1.f, 1.f),0),
        true
      },
      {
        OrientedRectangle(vec2(2, 1.5f), vec2(4, 1), 0),
        OrientedRectangle(vec2(2, -0.5f), vec2(2.f, 1.f),0),
        true
      },
      {
        OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 0),
        OrientedRectangle(vec2(-2.75, 1.75f), vec2(1.5f, 1.5f),0),
        true
      },
      {
        // barely miss; may have to zoom in to see
        OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 0),
        OrientedRectangle(vec2(-2.75, -1.05f), vec2(1.5f, 1.5f),30),
        false
      },
      {
        // barely miss; may have to zoom in to see
        OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 0),
        OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),30),
        true
      },
      {
        // barely miss; may have to zoom in to see
        OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 30),
        OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),0),
        false
      },
      {
        // barely miss; may have to zoom in to see
        OrientedRectangle(vec2(-3.5, 3.f), vec2(3, 2), 30),
        OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),0),
        true
      },
      {
        // barely miss; may have to zoom in to see
        OrientedRectangle(vec2(-3.5, 3.f), vec2(3, 2), 30),
        OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),40),
        false
      },
      {
        // barely miss; may have to zoom in to see
        OrientedRectangle(vec2(-3.5, 3.f), vec2(3, 2), 8),
        OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),40),
        true
      },
      
    };
  
    for(int i = 0; i < rectangleRectangleTests.size(); ++i){
      rectangleRectangleTest t = rectangleRectangleTests[i];

      // std::cout << "Test " << i<< " Verts: \n";
      // std::cout << "Rectangle 1: \n";
      // for(int i = 0; i < t.r1.vertices.size(); ++i){
      //   std::cout << t.r1.vertices[i]<<",";
      // }
      // std::cout<<"\n";
      // std::cout << "Rectangle 2: \n";
      // for(int i = 0; i < t.r2.vertices.size(); ++i){
      //   std::cout << t.r2.vertices[i]<<",";
      // }
      // std::cout<<"\n\n";
      
      EXPECT_EQ(OrientedRectangleOrientedRectangle(t.r1, t.r2), t.want) << i;
    }
  }


/* 
Test SATCollision
  - SATCollision; copy and paste other tests
*/
TEST(Geometry2D, SATCircleCircle){
  struct circleCircleTest{
    Circle c1;
    Circle c2;
    bool want;
  };

  std::vector<circleCircleTest> circleCircleTests = {
    {
      Circle(vec2(), 2),
      Circle(vec2(1,1), 1),
      true
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(2,2), 1),
      true
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(1,1.5), 1),
      true
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(2,3), 1),
      false
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(3,1), 1),
      false
    },
    {
      Circle(vec2(), 2),
      Circle(vec2(3,1), 1.5),
      true
    },

  };

  for(int i = 0; i < circleCircleTests.size(); ++i){
    circleCircleTest t = circleCircleTests[i];
    
    EXPECT_EQ(SATCollision(t.c1, t.c2), t.want);
  }
}

TEST(Geometry2D, SATCircleRectangle2D){
  struct circleRectangleTest{
    Circle c1;
    Rectangle2D r1;
    bool want;
  };

  std::vector<circleRectangleTest> circleRectangleTests = {
    {
      Circle(vec2(), 1),
      Rectangle2D(vec2(1,1), vec2(1,1)),
      false
    },
    {
      Circle(vec2(0,2), 2),
      Rectangle2D(vec2(.75,0.5), vec2(4,1)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(2,0.5), vec2(4, 0.95f)),
      false
    },
    {
      Circle(vec2(0,3), 1),
      Rectangle2D(vec2(-2.05, 3.5), vec2(2, 1.f)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(1,1), vec2(1,.5f)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(.5f,.75f), vec2(1.f,1.f)),
      true
    },
    {
      Circle(vec2(0,3), 2),
      Rectangle2D(vec2(.5f,.75f), vec2(1.f,0.5f)),
      true
    },
    {
      Circle(vec2(-2,-2.15), 2),
      Rectangle2D(vec2(0, 1.25f), vec2(2.f,1.f)),
      false
    },
    
  };

  for(int i = 0; i < circleRectangleTests.size(); ++i){
    circleRectangleTest t = circleRectangleTests[i];
    
    EXPECT_EQ(SATCollision(t.c1, t.r1), t.want) << i;
  }

}
TEST(Geometry2D, SATCircleOrientedRectangle){
  struct circleOrientedRectangleTest{
    Circle c1;
    OrientedRectangle r1;
    bool want;
  };

  std::vector<circleOrientedRectangleTest> circleOrientedRectangleTests = {
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(1,1), vec2(.5,.5), 0),
      true
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(2,1), vec2(2,1.f), 0),
      true
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(2,0.5), vec2(2, 0.95f *.5f), 0),
      false
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(.5f,.5f), vec2(0.5f,0.25f), 0),
      false
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(.5f,.70f), vec2(0.5f,0.25f), 0),
      false
    },
    {
      Circle(vec2(0,3), 2),
      OrientedRectangle(vec2(.5f,.75f), vec2(.5f,.5f), 0),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), 0),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), 90),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), 45),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), -45),
      true
    },
    {
      Circle(vec2(0,0), 1),
      OrientedRectangle(vec2(0.0f, 1.5f), vec2(2.f, 0.5f), -30),
      true
    },
    {
      Circle(vec2(-1,-1), 1),
      OrientedRectangle(vec2(-.5, 1.5f), vec2(2.f, 0.5f), -30),
      false
    },
    {
      Circle(vec2(-1,-1), 1),
      OrientedRectangle(vec2(-.5, -1.5f), vec2(2.f, 0.5f), -30),
      true
    },
    {
      Circle(vec2(-1,-1), 1),
      OrientedRectangle(vec2(-.5, -1.5f), vec2(2.25f, 1.f), -30),
      true
    },
    {
      Circle(vec2(-2,-2.15), 2),
      OrientedRectangle(vec2(0, 1.25f), vec2(2.f,1.f), 0),
      false
    },
  };

  for(int i = 0; i < circleOrientedRectangleTests.size(); ++i){
    circleOrientedRectangleTest t = circleOrientedRectangleTests[i];

    std::cout << "Test " << i<< " Verts: \n";
    std::cout << "Rectangle 1: \n";
    for(int i = 0; i < t.r1.vertices.size(); ++i){
      std::cout << t.r1.vertices[i]<<",";
    }
    std::cout<<"\n";
    std::cout << "Circle: \n";
    for(int i = 0; i < t.c1.vertices.size(); ++i){
      std::cout << t.c1.vertices[i]<<",";
    }
    std::cout << t.c1.radius<<",";
    std::cout<<"\n\n";

    EXPECT_EQ(SATCollision(t.c1, t.r1), t.want) << i;
  }

}


TEST(Geometry2D, SATRectangle2DRectangle2D){
  struct rectangleRectangleTest{
    Rectangle2D c1;
    Rectangle2D c2;
    bool want;
  };

  std::vector<rectangleRectangleTest> rectangleRectangleTests = {
    {
      Rectangle2D(vec2(2, 0.5f), vec2(4, 1)),
      Rectangle2D(vec2(1.5, 0.5f), vec2(1.f, 1.f)),
      true
    },
    {
      Rectangle2D(vec2(2, 1.5f), vec2(4, 1)),
      Rectangle2D(vec2(2, -0.5f), vec2(2.f, 1.f)),
      false
    },
    {
      Rectangle2D(vec2(-4.5, 3.f), vec2(3, 2)),
      Rectangle2D(vec2(-2.75, 1.75f), vec2(1.5f, 1.5f)),
      true
    },
    
  };

  for(int i = 0; i < rectangleRectangleTests.size(); ++i){
    rectangleRectangleTest t = rectangleRectangleTests[i];
    
    EXPECT_EQ(SATCollision(t.c1, t.c2), t.want) << i;
  }
}

TEST(Geometry2D, SATRectangle2DOrientedRectangle){
  struct rectangleRectangleTest{
    Rectangle2D r1;
    OrientedRectangle r2;
    bool want;
  };

  std::vector<rectangleRectangleTest> rectangleRectangleTests = {
    {
      Rectangle2D(vec2(2, 0.5f), vec2(4, 1)),
      OrientedRectangle(vec2(1.5, 0.5f), vec2(1.f, 1.f),0),
      true
    },
    {
      Rectangle2D(vec2(2, 1.5f), vec2(4, 1)),
      OrientedRectangle(vec2(2, -0.5f), vec2(2.f, 1.f),0),
      false
    },
    {
      Rectangle2D(vec2(-4.5, 3.f), vec2(3, 2)),
      OrientedRectangle(vec2(-2.75, 1.75f), vec2(1.5f, 1.5f),0),
      true
    },
    
  };

  for(int i = 0; i < rectangleRectangleTests.size(); ++i){
    rectangleRectangleTest t = rectangleRectangleTests[i];
    
    EXPECT_EQ(RectangleOrientedRectangle(t.r1, t.r2), t.want) << i;
  }
}
TEST(Geometry2D, SATOrientedRectangleOrientedRectangle){
  struct rectangleRectangleTest{
    OrientedRectangle r1;
    OrientedRectangle r2;
    bool want;
  };

  std::vector<rectangleRectangleTest> rectangleRectangleTests = {
    {
      OrientedRectangle(vec2(2, 0.5f), vec2(4, 1), 0),
      OrientedRectangle(vec2(1.5, 0.5f), vec2(1.f, 1.f),0),
      true
    },
    {
      OrientedRectangle(vec2(2, 1.5f), vec2(4, 1), 0),
      OrientedRectangle(vec2(2, -0.5f), vec2(2.f, 1.f),0),
      true
    },
    {
      OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 0),
      OrientedRectangle(vec2(-2.75, 1.75f), vec2(1.5f, 1.5f),0),
      true
    },
    {
      // barely miss; may have to zoom in to see
      OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 0),
      OrientedRectangle(vec2(-2.75, -1.05f), vec2(1.5f, 1.5f),30),
      false
    },
    {
      // barely miss; may have to zoom in to see
      OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 0),
      OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),30),
      true
    },
    {
      // barely miss; may have to zoom in to see
      OrientedRectangle(vec2(-4.5, 3.f), vec2(3, 2), 30),
      OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),0),
      false
    },
    {
      // barely miss; may have to zoom in to see
      OrientedRectangle(vec2(-3.5, 3.f), vec2(3, 2), 30),
      OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),0),
      true
    },
    {
      // barely miss; may have to zoom in to see
      OrientedRectangle(vec2(-3.5, 3.f), vec2(3, 2), 30),
      OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),40),
      false
    },
    {
      // barely miss; may have to zoom in to see
      OrientedRectangle(vec2(-3.5, 3.f), vec2(3, 2), 8),
      OrientedRectangle(vec2(-2.75, -1.0f), vec2(1.5f, 1.5f),40),
      true
    },
    
  };

  for(int i = 0; i < rectangleRectangleTests.size(); ++i){
    rectangleRectangleTest t = rectangleRectangleTests[i];
    
    EXPECT_EQ(SATCollision(t.r1, t.r2), t.want) << i;
  }
}

