#include "Matrix.h"
#include <cmath>
#include <cfloat>

void Transpose(const float *srcMat, float *dstMat, int srcRows, int srcCols){
  for(int i = 0; i < srcRows * srcCols; ++i){
    int row = i /srcRows;
    int col = i % srcRows;
    dstMat[i] = srcMat[srcCols * col + row];
  }
}

mat2::mat2(float f11, float f12, float f21, float f22){
  _11 = f11; _12 = f12; _21 = f21; _22 = f22;
};

mat2 Transpose(const mat2& matrix){
  mat2 result;
  Transpose(matrix.asArray, result.asArray, 2, 2);
  return result;
}

mat3:: mat3(float f11, float f12, float f13, float f21, float f22, float f23, float f31, float f32, float f33){
  _11 = f11; _12 = f12; _13 = f13; 
  _21 = f21; _22 = f22; _23 = f23;
  _31 = f31; _32 = f32; _33 = f33;
};
mat3 Transpose(const mat3& matrix){
  mat3 result;
  Transpose(matrix.asArray, result.asArray, 3, 3);
  return result;
}

mat4::mat4(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44){
  _11 = f11; _12 = f12; _13 = f13; 
  _21 = f21; _22 = f22; _23 = f23;
  _31 = f31; _32 = f32; _33 = f33;
};
mat4 Transpose(const mat4& matrix){
  mat4 result;
  Transpose(matrix.asArray, result.asArray, 4, 4);
  return result;
}




