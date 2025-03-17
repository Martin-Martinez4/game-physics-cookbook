#ifndef LINEAR_MATH_MATRIX_H_
#define LINEAR_MATH_MATRIX_H_

#include "Vector.h"

void Transpose(const float *srcMat, float *dstMat, int srcRows, int srcCols);
bool Multiply(float* out, const float* m1, int m1Rows, int m1Cols, const float* m2, int m2Rows, int m2Cols);
void Cofactor(float* out, const float* minor, int rows, int cols);

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

mat2 Transpose(const mat2& mat);
mat2 Minor(const mat2& mat);
mat2 Cofactor(const mat2& mat);
float Determinant(const mat2& mat);
// transpose of cofactor matrix
mat2 Adjugate(const mat2& mat);
mat2 Inverse(const mat2& mat);

mat2 operator*(const mat2& mat, float scalar);
mat2 operator*(const mat2& m1, const mat2& m2);
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

mat3 Transpose(const mat3& mat);
mat2 SubMatrix(const mat3& mat, int row, int col);
mat3 Minor(const mat3& mat);
mat3 Cofactor(const mat3& mat);
float Determinant(const mat3& mat);
mat3 Adjugate(const mat3& mat);
mat3 Inverse(const mat3& mat);

mat3 operator*(const mat3& matrix, float scalar);
mat3 operator*(const mat3& m1, const mat3& m2);
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
mat3 SubMatrix(const mat4& mat, int row, int col);
mat4 Minor(const mat4& mat);
mat4 Cofactor(const mat4& mat);
float Determinant(const mat4& mat);
mat4 Adjugate(const mat4& mat);
mat4 Inverse(const mat4& mat);

mat4 operator*(const mat4& matrix, float scalar);
mat4 operator*(const mat4& m1, const mat4& m2);
bool operator==(const mat4& l, const mat4& r);
bool operator!=(const mat4& l, const mat4& r);

mat4 Translation(float x, float y, float z);
mat4 Translation(const vec3& pos);
vec3 GetTranslation(const mat4& mat);

mat4 Scale(float x, float y, float z);
mat4 Scale(const vec3& vec);
vec3 GetScale(const mat4& mat);

mat4 XRotation(float angle);
mat3 XRotation3x3(float angle);

mat4 YRotation(float angle);
mat3 YRotation3x3(float angle);

mat4 ZRotation(float angle);
mat3 ZRotation3x3(float angle);

mat4 Rotation(float pitch, float yaw, float roll);
mat3 Rotation3x3(float pitch, float yaw, float roll);

mat4 AxisAngle(const vec3& axis, float angle);
mat3 AxisAngle3x3(const vec3& axis, float angle);

vec3 MultiplyPoint(const vec3& vec, const mat4& mat);
vec3 MultiplyVector(const vec3& vec, const mat4& mat);
vec3 MultiplyVector(const vec3& vec, const mat3& mat);

mat4 Transform(const vec3& scale, const vec3& eulerRotation, const vec3& translate);
mat4 Transform(const vec3& scale, const vec3& rotationAxis, float rotationAngle, const vec3& translate);

mat4 LookAt(const vec3& position, const vec3& target, const vec3& up);

mat4 Projection(float fov, float aspect, float zNear, float zFar);
mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

#endif