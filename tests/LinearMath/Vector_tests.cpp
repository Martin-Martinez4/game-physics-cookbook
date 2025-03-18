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
  EXPECT_EQ(vec2(1.456f, 2.25f), vec2(1.456f, 2.25f));
  EXPECT_EQ(vec2(), vec2(0, 0));

  EXPECT_EQ(vec3(1, 2, 3), vec3(1, 2, 3));
  EXPECT_EQ(vec3(1.123f, 2.25f, 3.33f), vec3(1.123f, 2.25f, 3.33f));
  EXPECT_EQ(vec3(-9.25f, 8.5225f, -2.56f), vec3(-9.25f, 8.5225f, -2.56f));

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
  EXPECT_FLOAT_EQ(Dot(vec2(1.22f,2.25f), vec2(4.33f,5.25f)), 17.0951f);
  EXPECT_FLOAT_EQ(Dot(vec2(-1.22f,2.f), vec2(4.33f,-5.f)), -15.2826f);

  EXPECT_FLOAT_EQ(Dot(vec3(1,2,3), vec3(4,5,6)), 32);
  EXPECT_FLOAT_EQ(Dot(vec3(1.22f, 2, 2.25f), vec3(4.33f, 5, 1)), 17.5326f);
  EXPECT_FLOAT_EQ(Dot(vec3(-1.22f, 2, -2.25f), vec3(4.33f,-5, 1)), -17.5326f);
  
}

TEST(VectorsTest, VectorCrossProduct){

  EXPECT_EQ(Cross(vec3(1,2,3), vec3(4,5,6)), vec3(-3, 6, -3));

  vec3 c1 = Cross(vec3(1.22f, 2, 2.25f), vec3(4.33f, 5, 2));
  EXPECT_EQ(c1, vec3(-7.25f, 7.3025f, -2.56f));
  EXPECT_FLOAT_EQ(c1.x, -7.25f);
  EXPECT_FLOAT_EQ(c1.y, 7.3025f);
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
      0.12435465f
    },
    {
      vec2{100,1},
      vec2{1,100},
      1.550796993f
    },
    {
      vec2{386,478},
      vec2{71,459},
      0.525848613200082f
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
      0.666946344503664f
    },
    {
      vec3{100,1, -41},
      vec3{1,100, 176},
      1.897235085837159f
    },
    {
      vec3{386,478,1},
      vec3{71,459,1},
      0.525847907836793f
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
      vec2{1.2307692307692307692307692307692f, 1.8461538461538461538461538461538f}
    },
    {
      vec2{100,1},
      vec2{1,100},
      vec2{0.019998000199980001999800019998f, 1.9998000199980001999800019998f}
    },
    {
      vec2{386,478},
      vec2{71,459},
      vec2{81.231251332733796274835204568843f, 525.14287833415228859365294221266f}
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
      vec3{1.571428571428571f,2.357142857142857f,0.785714285714286f}
    },
    {
      vec3{100,1, -41},
      vec3{1,100, 176},
      vec3{-0.171218000341655f,-17.121800034165507f,-30.134368060131293f}
    },
    {
      vec3{10,15,1},
      vec3{20,-5,1},
      vec3{5.915492957746479f,-1.47887323943662f,0.295774647887324f}
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
      vec2{-0.2307692307692307692307692307692f, 0.1538461538461538461538461538462f}
    },
    {
      vec2{100,1},
      vec2{1,100},
      vec2{99.980001999800019998000199980002f, -0.9998000199980001999800019998f}
    },
    {
      vec2{386,478},
      vec2{71,459},
      vec2{304.76874866726620372516479543116f, -47.14287833415228859365294221266f}
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
      vec3{0.379310344827586f, 0.068965517241379f, -0.241379310344828f}
    },
    {
      vec3{1, 2, 3},
      vec3{20, 30, 10},
      vec3{-0.571428571428571f, -0.357142857142857f, 2.214285714285714f}
    },
    {
      vec3{100, 1, -41},
      vec3{1, 100, 176},
      vec3{100.171218000341655f, 18.121800034165507f, -10.8656f}
    },
    {
      vec3{10,15,1},
      vec3{20,-5,1},
      vec3{4.084507042253521f, 16.47887323943662f, 0.704225352112676f}
    }
  };

  for(int i = 0; i < tests1.size(); ++i){
    vec3Test t = tests1[i];
    EXPECT_EQ(Perpendicular(t.v1, t.v2), t.want);
  }
}

