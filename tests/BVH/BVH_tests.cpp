#include <gtest/gtest.h>
#include "BVH.h"
#include <vector>

TEST(BVH, mortonCode){
  struct test {
    vec2 coords;
    int worldSize;
    unsigned short int want;
  };

  std::vector<test> tests = {
    {
     vec2(200,25),
     8,
     10
    },
    
  };

  for(int i = 0; i < tests.size(); ++i){
    test t = tests[i];
    EXPECT_EQ(calculateMortonCode(t.coords.x, t.coords.y, 0, 1200), t.want);
  }
}