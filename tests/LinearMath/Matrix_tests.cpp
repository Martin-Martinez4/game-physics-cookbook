#include <gtest/gtest.h>
#include "Matrix.h"
#include <vector>

// Matrix Equal
TEST(MatrixTest, MatrixEqual){

  struct mat2Test {
    mat2 m1;
    mat2 m2;
  };

  std::vector<mat2Test> mat2Tests = {
  {
      mat2{1,2,3,4},
      mat2{1,2,3,4}
    },
    {
      mat2{1.5,2.25,3.5,4.25},
      mat2{1.5,2.25,3.5,4.25}
    },
  };

  for(int i = 0; i < mat2Tests.size(); ++i){
    mat2Test t = mat2Tests[i];
    EXPECT_EQ(t.m1, t.m2);
  }

  struct mat3Test {
    mat3 m1;
    mat3 m2;
  };

  std::vector<mat3Test> mat3Tests = {
  {
      mat3{1,2,3,4,5,6,7,8,9},
      mat3{1,2,3,4,5,6,7,8,9}
    },
    {
      mat3{1.5,2.25,3.5,4.25,1.5,2.25,3.5,4.25,5.55},
      mat3{1.5,2.25,3.5,4.25,1.5,2.25,3.5,4.25,5.55}
    },
  };

  for(int i = 0; i < mat3Tests.size(); ++i){
    mat3Test t = mat3Tests[i];
    EXPECT_EQ(t.m1, t.m2);
  }


  struct mat4Test {
    mat4 m1;
    mat4 m2;
  };

  std::vector<mat4Test> mat4Tests = {
  {
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
    },
    {
      mat4{1.5,2.25,3.5,4.25,1.5,2.25,3.5,4.25,5.55,-1,-2,-3,-4,-5,-7,-8},
      mat4{1.5,2.25,3.5,4.25,1.5,2.25,3.5,4.25,5.55,-1,-2,-3,-4,-5,-7,-8}
    },
  };

  for(int i = 0; i < mat4Tests.size(); ++i){
    mat4Test t = mat4Tests[i];
    EXPECT_EQ(t.m1, t.m2);
  }
    
}

// Matrix Not Equal
TEST(MatrixTest, MatrixNotEqual){

  struct mat2Test {
    mat2 m1;
    mat2 m2;
  };

  std::vector<mat2Test> mat2Tests = {
  {
      mat2{1.1,2,3,4},
      mat2{1,2,3,4}
    },
    {
      mat2{1.5,2.25,3.52,4.25},
      mat2{1.5,2.25,3.5,4.25}
    },
  };

  for(int i = 0; i < mat2Tests.size(); ++i){
    mat2Test t = mat2Tests[i];
    EXPECT_NE(t.m1, t.m2);
  }

  struct mat3Test {
    mat3 m1;
    mat3 m2;
  };

  std::vector<mat3Test> mat3Tests = {
  {
      mat3{1,2,3,44,5,6,7,8,9},
      mat3{1,2,3,4,5,6,7,8,9}
    },
    {
      mat3{1.5,2.25,3.5,4,1.5,2.25,3.5,4.25,5.55},
      mat3{1.5,2.255,3.5,4.25,1.5,2.25,3.5,4.25,5.55}
    },
  };

  for(int i = 0; i < mat3Tests.size(); ++i){
    mat3Test t = mat3Tests[i];
    EXPECT_NE(t.m1, t.m2);
  }


  struct mat4Test {
    mat4 m1;
    mat4 m2;
  };

  std::vector<mat4Test> mat4Tests = {
  {
      mat4{1,2.1,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
    },
    {
        mat4{1.5,2.25,3.5,4.25,1.5,2.25,3.5,4.25,5.55,-1,-2,-3,-4,-5,-7,-8},
        mat4{1.5,2.225,3.5,4.25,1.5,2.25,3.5,4.25,5.55,-1,-2,-3,-4,-5,-7,-8}
      },
  };

  for(int i = 0; i < mat4Tests.size(); ++i){
    mat4Test t = mat4Tests[i];
    EXPECT_NE(t.m1, t.m2);
  }
}

// Matrix Transpose
TEST(MatrixTest, MatrixTranspose){
  struct mat2Test {
    mat2 m1;
    mat2 m2;
  };

  std::vector<mat2Test> mat2Tests = {
  {
      mat2{1,2,3,4},
      mat2{1,3,2,4}
    },
    {
        mat2{1.5,2.25,3.5,4.2},
        mat2{1.5,3.5,2.25,4.2}
      },
  };

  for(int i = 0; i < mat2Tests.size(); ++i){
    mat2Test t = mat2Tests[i];
    EXPECT_EQ(Transpose(t.m1), t.m2);
  }

  struct mat3Test {
    mat3 m1;
    mat3 m2;
  };

  std::vector<mat3Test> mat3Tests = {
  {
      mat3{1,2,3,4,5,6,7,8,9},
      mat3{1,4,7,2,5,8,3,6,9}
    },
    {
        mat3{1.5,2.225,3.5,4.2,5,6,7,8,9},
        mat3{1.5,4.2,7,2.225,5,8,3.5,6,9}
      },
  };

  for(int i = 0; i < mat3Tests.size(); ++i){
    mat3Test t = mat3Tests[i];
    EXPECT_EQ(Transpose(t.m1), t.m2);
  }

  struct mat4Test {
    mat4 m1;
    mat4 m2;
  };

  std::vector<mat4Test> mat4Tests = {
  {
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      mat4{1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16}
    },
    {
        mat4{1.5,2.25,3.5,4.2,1.5,2.25,3.5,4.25,5.55,-1,-2,-3,-4,-5,-7,-8},
        mat4{1.5,1.5,5.55,-4,2.25,2.25,-1,-5,3.5,3.5,-2,-7,4.2,4.25,-3,-8}
      },
  };

  for(int i = 0; i < mat4Tests.size(); ++i){
    mat4Test t = mat4Tests[i];
    EXPECT_EQ(Transpose(t.m1), t.m2);
  }
}

// Matrix multiplication

// identity?

// determinate 2 x 2

// cofactor

// determinates

// inverse

// translate

// scale

// rotation

// projection