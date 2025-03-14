#include "Matrix.h"
#include "Vector.h"
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

std::ostream& operator<<(std::ostream &os, const mat2& m){
  return os<<m._11 << ", " <<m._12 << ", " << m._21 << ", " << m._22;
}


mat2 Transpose(const mat2& matrix){
  mat2 result;
  Transpose(matrix.asArray, result.asArray, 2, 2);
  return result;
}
bool operator==(const mat2& l, const mat2& r){
  for(int i = 0; i < 4; ++i){
    if(!CMP(l.asArray[i], r.asArray[i])){
      return false;
    }
  }

  return true;
}

bool operator!=(const mat2& l, const mat2& r){
  for(int i = 0; i < 4; ++i){
    if(!CMP(l.asArray[i], r.asArray[i])){
      return true;
    }
  }

  return false;
}

mat3:: mat3(float f11, float f12, float f13, float f21, float f22, float f23, float f31, float f32, float f33){
  _11 = f11; _12 = f12; _13 = f13; 
  _21 = f21; _22 = f22; _23 = f23;
  _31 = f31; _32 = f32; _33 = f33;
};
std::ostream& operator<<(std::ostream &os, const mat3& m){
  return os<<m._11 << ", " <<m._12 << ", " << m._13 << ", "<< m._21 << ", " << m._22 << ", " << m._23 << ", " << m._31 << ", " << m._32 << ", " << m._33;
}

mat3 Transpose(const mat3& matrix){
  mat3 result;
  Transpose(matrix.asArray, result.asArray, 3, 3);
  return result;
}
bool operator==(const mat3& l, const mat3& r){
  for(int i = 0; i < 9; ++i){
    if(!CMP(l.asArray[i], r.asArray[i])){
      return false;
    }
  }

  return true;
}
bool operator!=(const mat3& l, const mat3& r){
  for(int i = 0; i < 9; ++i){
    if(!CMP(l.asArray[i], r.asArray[i])){
      return true;
    }
  }

  return false;
}

mat4::mat4(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44){
  _11 = f11; _12 = f12; _13 = f13; _14 = f14; 
  _21 = f21; _22 = f22; _23 = f23; _24 = f24;
  _31 = f31; _32 = f32; _33 = f33; _34 = f34;
  _41 = f41; _42 = f42; _43 = f43; _44 = f44;
};
std::ostream& operator<<(std::ostream &os, const mat4& m){
  return os<<m._11 << ", " <<m._12 << ", " << m._13 << ", " << m._14 << ", "<< m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << ", "<< m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34<< ", "<< m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44;
}
mat4 Transpose(const mat4& matrix){
  mat4 result;
  Transpose(matrix.asArray, result.asArray, 4, 4);
  return result;
}
bool operator==(const mat4& l, const mat4& r){
  for(int i = 0; i < 16; ++i){
    if(!CMP(l.asArray[i], r.asArray[i])){
      return false;
    }
  }

  return true;
}
bool operator!=(const mat4& l, const mat4& r){
  for(int i = 0; i < 16; ++i){
    if(!CMP(l.asArray[i], r.asArray[i])){
      return true;
    }
  }

  return false;
}



