#include <gtest/gtest.h>
#include "Vector.h"

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