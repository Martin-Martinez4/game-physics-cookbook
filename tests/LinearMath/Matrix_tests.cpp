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
TEST(MatrixTest, MatrixMultiply){
  struct matScalarTest {
    mat4 m1;
    float scalar;
    mat4 want;
  };

  std::vector<matScalarTest> matScalarTests = {
    {
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      2.0f,
      mat4{2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32},

    },
    {
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      .5f,
      mat4{.5f,1.f,1.5f,2.0f,2.5f,3,3.5f,4.f,4.5f,5.f,5.5f,6.f,6.5f,7.f,7.5f,8.f},

    },
  };

  for(int i = 0; i < matScalarTests.size(); ++i){
    matScalarTest t = matScalarTests[i];
    EXPECT_EQ(t.m1 * t.scalar, t.want);
  }

  struct matmatTest {
    mat4 m1;
    mat4 m2;
    mat4 want;
  };

  std::vector<matmatTest> matmatTests = {
    {
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      mat4{90,100,110,120,202,228,254,280,314,356,398,440,426,484,542,600},

    },
    {
      mat4{.5f,1,3,3.f/4.f,5,6,7,8,.5f,6.f/9.f,7,7.f/22.f,5,4,3,1},
      mat4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
      mat4{42.25,95.f/2.f,52.75,58,202,228,254,280,2342.f/33.f,874.f/11.f,2902.f/33.f,3182.f/33.f,65,78,91,104},

    },
  };

  for(int i = 0; i < matmatTests.size(); ++i){
    matmatTest t = matmatTests[i];
    EXPECT_EQ(t.m1 * t.m2, t.want);
  }


}

TEST(MatrixTest, MatrixDeterminates){
  struct det2x2Test {
    mat2 mat;
    float want;
  };

  std::vector<det2x2Test> det2x2Tests = {
    {
      mat2(1,2,3,4),
      -2.f
    },
    {
      mat2(10,0.25,.33333333,33),
      329.91666
    }
  };

  for(int i = 0; i < det2x2Tests.size(); ++i){
    det2x2Test t = det2x2Tests[i];
    EXPECT_EQ(Determinant(t.mat), t.want);
  }

  struct det3x3Test {
    mat3 mat;
    float want;
  };

  std::vector<det3x3Test> det3x3Tests = {
    {
      mat3(1,2,3,4,5,6,7,8,9),
      -0.f
    },
    {
      mat3(1,2,13,14,.5f,6,7,8,19),
      924.f
    }
  };

  for(int i = 0; i < det3x3Tests.size(); ++i){
    det3x3Test t = det3x3Tests[i];
    EXPECT_EQ(Determinant(t.mat), t.want);
  }

  struct det4x4Test {
    mat4 mat;
    float want;
  };

  std::vector<det4x4Test> det4x4Tests = {
    {
      mat4(1,3,5,9,1,3,1,7,4,3,9,7,5,2,0,9),
      -376.f
    },
    {
      mat4(1.5,3,5,9,1,3.5,1,7,4,3,9.5,7,5,2,0,9.5),
      -498.93749f
    }
  };

  for(int i = 0; i < det4x4Tests.size(); ++i){
    det4x4Test t = det4x4Tests[i];
    EXPECT_EQ(Determinant(t.mat), t.want);
  }
}

// inverse
TEST(MatrixTest, MatrixInverse){
  struct inverse4x4Test {
    mat4 mat;
    mat4 want;
  };

  std::vector<inverse4x4Test> inverse4x4Tests = {
    {
      mat4(2,2,3,3,4,4,5,5,7,7,8,8,9,9,10,10),
      mat4()
    },
    {
      mat4(10,5,3,4,8,10,4,5,10,9,8,8,9,9,10,10),
      mat4(18.f/167.f,-18.f/167.f,41.f/167.f,-31.f/167.f,-28.f/167.f,28.f/167.f,29.f/167.f,-26.f/167.f,-91.f/167.f,-76.f/167.f,303.f/167.f,-168.f/167.f,100.f/167.f,67.f/167.f,-366.f/167.f,236.f/167.f)
    }
  };

  for(int i = 0; i < inverse4x4Tests.size(); ++i){
    inverse4x4Test t = inverse4x4Tests[i];
    EXPECT_EQ(Inverse(t.mat), t.want);
  }
}
