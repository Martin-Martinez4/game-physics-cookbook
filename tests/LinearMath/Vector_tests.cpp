#include <gtest/gtest.h>
#include "Vector.h"

TEST(VectorsTest, VectorConstruction){
  vec2 vec2_0 = vec2{1, 2};
  vec2 vec2_1 = vec2{};

  EXPECT_EQ(vec2_0.x, 1);
  EXPECT_EQ(vec2_0.y, 2);

  EXPECT_EQ(vec2_1.x, 0);
  EXPECT_EQ(vec2_1.y, 0);
  
}