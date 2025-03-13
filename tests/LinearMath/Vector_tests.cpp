#include <gtest/gtest.h>
#include "Vector.h"
#include <vector>

TEST(VectorsTest, VectorConstruction){
  vec2 vec2_0 = vec2{1, 2};
  vec2 vec2_1 = vec2{};

  EXPECT_EQ(vec2_0.x, 1);
  EXPECT_EQ(vec2_0.y, 2);

  EXPECT_EQ(vec2_1.x, 0);
  EXPECT_EQ(vec2_1.y, 0);

  vec3 vec3_0 = vec3{1, 2, 3};
  vec3 vec3_1 = vec3{};

  EXPECT_EQ(vec3_0.x, 1);
  EXPECT_EQ(vec3_0.y, 2);
  EXPECT_EQ(vec3_0.z, 3);

  EXPECT_EQ(vec3_1.x, 0);
  EXPECT_EQ(vec3_1.y, 0);
  EXPECT_EQ(vec3_1.z, 0);
  
}

TEST(VectorsTest, VectorEqual){

  EXPECT_EQ(vec2(1, 2), vec2(1, 2));
  EXPECT_EQ(vec2(1.456, 2.25), vec2(1.456, 2.25));
  EXPECT_EQ(vec2(), vec2(0, 0));

  EXPECT_EQ(vec3(1, 2, 3), vec3(1, 2, 3));
  EXPECT_EQ(vec3(1.123, 2.25, 3.33), vec3(1.123, 2.25, 3.33));
  EXPECT_EQ(vec3(-9.25, 8.5225, -2.56), vec3(-9.25, 8.5225, -2.56));

  EXPECT_EQ(vec3(), vec3());
  EXPECT_EQ(vec3(), vec3(0, 0, 0));
  
}

TEST(VectorsTest, VectorMathOperators){

  EXPECT_EQ(vec2(1, 2) + vec2(20, 19), vec2(21, 21));
  EXPECT_EQ(vec2(0, 0) - vec2(20, 19), vec2(-20, -19));

  EXPECT_EQ(vec3(1, 2, 3) + vec3(20, 19, 18), vec3(21, 21, 21));
  EXPECT_EQ(vec3(0, 0, 0) - vec3(20, 19, 18), vec3(-20, -19, -18));

  EXPECT_EQ(vec2(1.5, 2.25) * vec2(2, 4), vec2(3, 9));

  EXPECT_EQ(vec3(1.25, 2.5, 3.25) * vec3(4, 2, 8), vec3(5, 5, 26)); 
}

TEST(VectorsTest, VectorDotProduct){

  EXPECT_FLOAT_EQ(Dot(vec2(1,2), vec2(4,5)), 14);
  EXPECT_FLOAT_EQ(Dot(vec2(1.22,2.25), vec2(4.33,5.25)), 17.0951);
  EXPECT_FLOAT_EQ(Dot(vec2(-1.22,2), vec2(4.33,-5)), -15.2826);

  EXPECT_FLOAT_EQ(Dot(vec3(1,2,3), vec3(4,5,6)), 32);
  EXPECT_FLOAT_EQ(Dot(vec3(1.22, 2, 2.25), vec3(4.33, 5, 1)), 17.5326);
  EXPECT_FLOAT_EQ(Dot(vec3(-1.22, 2, -2.25), vec3(4.33,-5, 1)), -17.5326);
  
}

TEST(VectorsTest, VectorCrossProduct){

  EXPECT_EQ(Cross(vec3(1,2,3), vec3(4,5,6)), vec3(-3, 6, -3));

  vec3 c1 = Cross(vec3(1.22, 2, 2.25), vec3(4.33, 5, 2));
  EXPECT_EQ(c1, vec3(-7.25, 7.3025, -2.56));
  EXPECT_FLOAT_EQ(c1.x, -7.25);
  EXPECT_FLOAT_EQ(c1.y, 7.3025);
  // EXPECT_EQ(Cross(vec3(-1.22, 2, -2.25), vec3(4.33,-5, 1)), vec3(-9.25, -8.5225, -2.56));
  
}

// angle, project, perpendicular, reflection, 
TEST(VectorsTest, VectorAngleBetween){
  struct vec2Test {
    vec2 v1;
    vec2 v2;
    float want;
  };

  std::vector<vec2Test> tests = {
    {
      vec2{1,1},
      vec2{1,1},
      0
    },
    {
      vec2{1,2},
      vec2{20,30},
      0.12435465
    },
    {
      vec2{100,1},
      vec2{1,100},
      1.550796993
    },
    {
      vec2{386,478},
      vec2{71,459},
      0.525848613200082
    }
  };

  for(int i = 0; i < tests.size(); ++i){
    vec2Test t = tests[i];
    EXPECT_FLOAT_EQ(Angle(t.v1, t.v2), t.want);
  }

   struct vec3Test {
    vec3 v1;
    vec3 v2;
    float want;
  };

  std::vector<vec3Test> tests1 = {
    {
      vec3{1,1, 100},
      vec3{1,1, 100},
      0
    },
    {
      vec3{1,2,3},
      vec3{20,30,10},
      0.666946344503664
    },
    {
      vec3{100,1, -41},
      vec3{1,100, 176},
      1.897235085837159
    },
    {
      vec3{386,478,1},
      vec3{71,459,1},
      0.525847907836793
    }
  };

  for(int i = 0; i < tests1.size(); ++i){
    vec3Test t = tests1[i];
    EXPECT_FLOAT_EQ(Angle(t.v1, t.v2), t.want);
  }
}

TEST(VectorsTest, VectorProjection){
  struct vec2Test {
    vec2 v1;
    vec2 v2;
    vec2 want;
  };

  std::vector<vec2Test> tests = {
    {
      vec2{1,1},
      vec2{1,1},
      vec2{1,1}
    },
    {
      vec2{1,2},
      vec2{20,30},
      vec2{1.2307692307692307692307692307692, 1.8461538461538461538461538461538}
    },
    {
      vec2{100,1},
      vec2{1,100},
      vec2{0.019998000199980001999800019998, 1.9998000199980001999800019998}
    },
    {
      vec2{386,478},
      vec2{71,459},
      vec2{81.231251332733796274835204568843, 525.14287833415228859365294221266}
    }
  };

  for(int i = 0; i < tests.size(); ++i){
    vec2Test t = tests[i];
    EXPECT_EQ(Project(t.v1, t.v2), t.want);
  }

   struct vec3Test {
    vec3 v1;
    vec3 v2;
    vec3 want;
  };

  std::vector<vec3Test> tests1 = {
    {
      vec3{1, 1, 100},
      vec3{1, 1, 100},
      vec3{1, 1, 100}
    },
    {
      vec3{1, 2, 3},
      vec3{20, 30, 10},
      vec3{1.571428571428571,2.357142857142857,0.785714285714286}
    },
    {
      vec3{100,1, -41},
      vec3{1,100, 176},
      vec3{-0.171218000341655,-17.121800034165507,-30.134368060131293}
    },
    {
      vec3{10,15,1},
      vec3{20,-5,1},
      vec3{5.915492957746479,-1.47887323943662,0.295774647887324}
    }
  };

  for(int i = 0; i < tests1.size(); ++i){
    vec3Test t = tests1[i];
    EXPECT_EQ(Project(t.v1, t.v2), t.want);
  }
}

TEST(VectorsTest, VectorPerpendicular){
  struct vec2Test {
    vec2 v1;
    vec2 v2;
    vec2 want;
  };

  std::vector<vec2Test> tests = {
    {
      vec2{1,1},
      vec2{1,1},
      vec2{0,0}
    },
    {
      vec2{1,2},
      vec2{20,30},
      vec2{-0.2307692307692307692307692307692, 0.1538461538461538461538461538462}
    },
    {
      vec2{100,1},
      vec2{1,100},
      vec2{99.980001999800019998000199980002, -0.9998000199980001999800019998}
    },
    {
      vec2{386,478},
      vec2{71,459},
      vec2{304.76874866726620372516479543116, -47.14287833415228859365294221266}
    }
  };

  for(int i = 0; i < tests.size(); ++i){
    vec2Test t = tests[i];
    EXPECT_EQ(Perpendicular(t.v1, t.v2), t.want);
  }

   struct vec3Test {
    vec3 v1;
    vec3 v2;
    vec3 want;
  };

  std::vector<vec3Test> tests1 = {
    {
      vec3{1, 1, 1},
      vec3{20, 30, 40},
      vec3{0.379310344827586, 0.068965517241379, -0.241379310344828}
    },
    {
      vec3{1, 2, 3},
      vec3{20, 30, 10},
      vec3{-0.571428571428571, -0.357142857142857, 2.214285714285714}
    },
    {
      vec3{100, 1, -41},
      vec3{1, 100, 176},
      vec3{100.171218000341655, 18.121800034165507, -10.8656}
    },
    {
      vec3{10,15,1},
      vec3{20,-5,1},
      vec3{4.084507042253521, 16.47887323943662, 0.704225352112676}
    }
  };

  for(int i = 0; i < tests1.size(); ++i){
    vec3Test t = tests1[i];
    EXPECT_EQ(Perpendicular(t.v1, t.v2), t.want);
  }
}

