#ifndef LINEAR_MATH_MATRIX_H_
#define LINEAR_MATH_MATRIX_H_

#include "Vector.h"

void Transpose(const float *srcMat, float *dstMat, int srcRows, int srcCols);

typedef struct mat2{

  inline mat2(){
    _11 = _22 = 1.0f;
    _12 = _21 = 0.0f;
  }

  mat2(float f11, float f12, float f21, float f22);

  union{
    struct{
      float _11, _12, _21, _22;
    };
    float asArray[4];
  };
  inline float* operator[](int i){
    return &(asArray[i * 2]);
  }
  friend std::ostream& operator<<(std::ostream &os, const mat2& m);

} mat2;

mat2 Transpose(const mat2& matrix);
bool operator==(const mat2& l, const mat2& r);
bool operator!=(const mat2& l, const mat2& r);


typedef struct mat3{

   inline mat3(){
    _11 = _22 = _33 = 1.0f;
    _12 = _13 = _21 = 0.0f;
    _23 = _31 = _32 = 0.0f;
  }

  mat3(float f11, float f12, float f13, float f21, float f22, float f23, float f31, float f32, float f33);

  union{
    struct{
      float _11, _12, _13, _21, _22, _23, _31, _32, _33;
    };
    float asArray[9];
  };
  inline float* operator[](int i){
    return &(asArray[i * 3]);
  }
  friend std::ostream& operator<<(std::ostream &os, const mat3& m);

} mat3;

mat3 Transpose(const mat3& matrix);
bool operator==(const mat3& l, const mat3& r);
bool operator!=(const mat3& l, const mat3& r);

typedef struct mat4{

   inline mat4(){
    _11 = _22 = _33 = _44 = 1.0f;
    _12 = _13 = _14 = _21 = 0.0f;
    _23 = _24 = _31 = _32 = 0.0f;
    _34 = _41 = _42 = _43 = 0.0f;
  }

  mat4(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44);

  union{
    struct{
      float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44;
    };
    float asArray[16];
  };
  inline float* operator[](int i){
    return &(asArray[i * 4]);
  }
  friend std::ostream& operator<<(std::ostream &os, const mat4& m);

} mat4;

mat4 Transpose(const mat4& matrix);
bool operator==(const mat4& l, const mat4& r);
bool operator!=(const mat4& l, const mat4& r);

#endif