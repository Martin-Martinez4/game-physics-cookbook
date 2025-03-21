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

bool Multiply(float* out, const float* m1, int m1Rows, int m1Cols, const float* m2, int m2Rows, int m2Cols){
  if(m1Cols != m2Rows){
    return false;
  }

  for(int i = 0; i < m1Rows; ++i){
    for(int j = 0; j < m2Cols; ++j){
      out[m2Cols * i +j] = 0.0f;
      for(int k = 0; k < m2Rows; ++k){
        int a = m1Cols * i + k;
        int b = m2Cols * k + j;
        out[m2Cols * i + j] += m1[a] * m2[b];
      }
    }
  }

  return true;
}

void Cofactor(float* out, const float* minor, int rows, int cols){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      // target index
      int t = cols * j + i;

      // source index
      int s = cols * j + i;

      // + or -
      float sign = powf(-1.0f, i + j);
      out[t] = minor[s] * sign;
    }
  }
}


mat2::mat2(float f11, float f12, float f21, float f22){
  _11 = f11; _12 = f12; _21 = f21; _22 = f22;
};

std::ostream& operator<<(std::ostream &os, const mat2& m){
  return os<<m._11 << ", " <<m._12 << ", " << m._21 << ", " << m._22;
}


mat2 Transpose(const mat2& mat){
  mat2 result;
  Transpose(mat.asArray, result.asArray, 2, 2);
  return result;
}

mat2 Minor(const mat2& mat){
  return mat2{
    mat._22, mat._21,
    mat._12, mat._11
  };
}
mat2 Cofactor(const mat2& mat){
  mat2 result;
  Cofactor(result.asArray, Minor(mat).asArray, 2, 2);
  return result;
}
float Determinant(const mat2& mat){
  return mat._11 * mat._22 - mat._12 * mat._21;
}
mat2 Adjugate(const mat2& mat){
  return Transpose(Cofactor(mat));
}
mat2 Inverse(const mat2& mat){
  float det = Determinant(mat);
  if(CMP(det, 0.0f)){ return mat2(); }
  return Adjugate(mat) * (1.0f / det);
}


mat2 operator*(const mat2& mat, float scalar){
  mat2 result;
  for(int i = 0; i < 4; ++i){
    result.asArray[i] = mat.asArray[i] * scalar;
  }
  return result;
}
mat2 operator*(const mat2& m1, const mat2& m2){
  mat2 res;
  Multiply(res.asArray, m1.asArray, 2, 2, m2.asArray, 2, 2);
  return res;
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

mat3 Transpose(const mat3& mat){
  mat3 result;
  Transpose(mat.asArray, result.asArray, 3, 3);
  return result;
}
mat2 SubMatrix(const mat3& mat, int row, int col){
  mat2 result;
  int index = 0;

  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if(i == row || j == col){
        continue;
      }

      int target = index++;
      int source = 3 * i + j;
      result.asArray[target] = mat.asArray[source];
    }
  }
  return result;
}
mat3 Minor(const mat3& mat){
  mat3 result;

  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      result[i][j] = Determinant(SubMatrix(mat, i, j));
    }
  }

  return result;
}
mat3 Cofactor(const mat3& mat){
  mat3 result;
  Cofactor(result.asArray, Minor(mat).asArray, 3, 3);
  return result;
}
float Determinant(const mat3& mat){
  float result = 0.0f;
  mat3 cofactor = Cofactor(mat);
  for(int j = 0; j < 3; ++j){
    int index = 3 * 0 + j;
    result += mat.asArray[index] * cofactor[0][j];
  }

  return result;
}
mat3 Adjugate(const mat3& mat){
  return Transpose(Cofactor(mat));
}
mat3 Inverse(const mat3& mat){
  float det = Determinant(mat);
  if(CMP(det, 0.0f)){ return mat3(); }
  return Adjugate(mat) * (1.0f / det);
}

mat3 operator*(const mat3& mat, float scalar){
  mat3 result;
  for(int i = 0; i < 9; ++i){
    result.asArray[i] = mat.asArray[i] * scalar;
  }
  return result;
}
mat3 operator*(const mat3& m1, const mat3& m2){
  mat3 res;
  Multiply(res.asArray, m1.asArray, 3, 3, m2.asArray, 3, 3);
  return res;
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
mat3 SubMatrix(const mat4& mat, int row, int col){
  mat3 result;
  int index = 0;

  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < 4; ++j){
      if(i == row || j == col){
        continue;
      }

      int target = index++;
      int source = 4 * i + j;
      result.asArray[target] = mat.asArray[source];
    }
  }

  return result;
}

// matrix of minors aka determinate of submatrix
mat4 Minor(const mat4& mat){
  mat4 result;

  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < 4; ++j){
      result[i][j] = Determinant(SubMatrix(mat, i, j));
    }
  }

  return result;
}
mat4 Cofactor(const mat4& mat){
  mat4 result;
  Cofactor(result.asArray, Minor(mat).asArray, 4, 4);
  return result;
}
float Determinant(const mat4& mat){
  float result = 0.0f;

  mat4 cofactor = Cofactor(mat);
  for(int j = 0; j < 4; ++j){
    result += mat.asArray[4 * 0 + j] * cofactor[0][j];
  }

  return result;
}
mat4 Adjugate(const mat4& mat){
  return Transpose(Cofactor(mat));
}
mat4 Inverse(const mat4& mat){
  float det = Determinant(mat);
  if(CMP(det, 0.0f)){ return mat4(); }
  return Adjugate(mat) * (1.0f / det);
}

mat4 operator*(const mat4& mat, float scalar){
  mat4 result;
  for(int i = 0; i < 16; ++i){
    result.asArray[i] = mat.asArray[i] * scalar;
  }
  return result;
}
mat4 operator*(const mat4& m1, const mat4& m2){
  mat4 res;
  Multiply(res.asArray, m1.asArray, 4, 4, m2.asArray, 4, 4);
  return res;
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

mat4 Translation(float x, float y, float z){
  return mat4{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    x, y, z, 1.0f
  };
}
mat4 Translation(const vec3& pos){
  return mat4{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    pos.x, pos.y, pos.z, 1.0f
  };
}
vec3 GetTranslation(const mat4& mat){
  return vec3(mat._41, mat._42, mat._43);
}


mat4 Scale(float x, float y, float z){
  return mat4{
    x, 0.0f, 0.0f, 0.0f,
    0.0f, y, 0.0f, 0.0f,
    0.0f, 0.0f, z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
}
mat4 Scale(const vec3& vec){
  return mat4{
    vec.x, 0.0f, 0.0f, 0.0f,
    0.0f, vec.y, 0.0f, 0.0f,
    0.0f, 0.0f, vec.z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
}
vec3 GetScale(const mat4& mat){
  return vec3(mat._11, mat._22, mat._33);
}

mat4 XRotation(float angle){
  angle = DEG2RAD(angle);
  return mat4{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cosf(angle), sinf(angle), 0.0f,
    0.0f, -sinf(angle), cosf(angle), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
}
mat3 XRotation3x3(float angle){
  angle = DEG2RAD(angle);
  return mat3{
    1.0f, 0.0f, 0.0f,
    0.0f, cosf(angle), sinf(angle),
    0.0f, -sinf(angle), cosf(angle)
  };
}

mat4 YRotation(float angle){
  angle = DEG2RAD(angle);
  return mat4{
    cosf(angle),  0.0f, -sinf(angle), 0.0f,
    0.0f,         1.0f, 0.0f,         0.0f,
    sinf(angle),  0.0f, cosf(angle),  0.0f,
    0.0f,         0.0f, 0.0f,         1.0f
  };
}
mat3 YRotation3x3(float angle){
angle = DEG2RAD(angle);
  return mat3{
    cosf(angle),  0.0f, -sinf(angle), 
    0.0f,         1.0f, 0.0f,         
    sinf(angle),  0.0f, cosf(angle),  
  };
}

mat4 ZRotation(float angle){
  angle = DEG2RAD(angle);
  return mat4{
    cosf(angle), sinf(angle), 0.0f, 0.0f,
    -sinf(angle), cosf(angle), 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f 
  };
}
mat3 ZRotation3x3(float angle){
angle = DEG2RAD(angle);
  return mat3{
    cosf(angle), sinf(angle), 0.0f,
    -sinf(angle), cosf(angle), 0.0f, 
    0.0f, 0.0f, 1.0f, 
  };
}

mat4 Rotation(float pitch, float yaw, float roll){
  return ZRotation(roll) * XRotation(pitch) * YRotation(yaw);
}
mat3 Rotation3x3(float pitch, float yaw, float roll){
  return ZRotation3x3(roll) * XRotation3x3(pitch) * YRotation3x3(yaw);
}
mat2 Rotation2x2(float degrees){
  return mat2{
    cosf(degrees), -sinf(degrees),
    sin(degrees), cosf(degrees)
  };
}

mat4 AxisAngle(const vec3& axis, float angle){
  angle = DEG2RAD(angle);
  float c = cosf(angle);
  float s = sinf(angle);
  float t = 1.0f - cosf(angle);

  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  if(!CMP(MagnitudeSq(axis), 1.0f)){
    float invLen = 1.0f / Magnitude(axis);

    // Normalize x, y, and z
    x *= invLen;
    y *= invLen;
    z *= invLen;
  }

  return mat4{
    t*(x*x) + c, t*x*y + s*z, t*x*z - s*y, 0.0f,
    t*x*y - s*z, t*y*y + c, t*y*z + s*x, 0.0f,
    t*x*z + s*y, t*y*z - s*x, t*z*z + c, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
}
mat3 AxisAngle3x3(const vec3& axis, float angle){
  angle = DEG2RAD(angle);
  float c = cosf(angle);
  float s = sinf(angle);
  float t = 1.0f - cosf(angle);

  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  if(!CMP(MagnitudeSq(axis), 1.0f)){
    float invLen = 1.0f / Magnitude(axis);

    // Normalize x, y, and z
    x *= invLen;
    y *= invLen;
    z *= invLen;
  }

  return mat3{
    t*(x*x) + c, t*x*y + s*z, t*x*z - s*y, 
    t*x*y - s*z, t*y*y + c, t*y*z + s*x, 
    t*x*z + s*y, t*y*z - s*x, t*z*z + c, 
  };
}


vec3 MultiplyPoint(const vec3& vec, const mat4& mat){
  vec3 result;
  result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31 + 1.0f * mat._41;
  result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32 + 1.0f * mat._42;
  result.z = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33 + 1.0f * mat._43;

  return result;
}

vec3 MultiplyVector(const vec3& vec, const mat4& mat){
  vec3 result;
  result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31 + 0.0f * mat._41;
  result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32 + 0.0f * mat._42;
  result.z = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33 + 0.0f * mat._43;

  return result;
}
vec3 MultiplyVector(const vec3& vec, const mat3& mat){
  vec3 result;
  result.x = Dot(vec, vec3(mat._11, mat._21, mat._31));
  result.y = Dot(vec, vec3(mat._12, mat._22, mat._32));
  result.z = Dot(vec, vec3(mat._13, mat._23, mat._33));

  return result;
}
vec2 MultiplyVector(const mat2& mat, const vec2& vec){
  return vec2{
    mat._11*vec.x + mat._12*vec.y,
    mat._21*vec.x + mat._22*vec.y
  };
}


mat4 Transform(const vec3& scale, const vec3& eulerRotation, const vec3& translate){
  return Scale(scale) * Rotation(eulerRotation.x, eulerRotation.y, eulerRotation.z) * Translation(translate);
}
mat4 Transform(const vec3& scale, const vec3& rotationAxis, float rotationAngle, const vec3& translate){
  return Scale(scale) * AxisAngle(rotationAxis, rotationAngle) * Translation(translate);
}

mat4 LookAt(const vec3& position, const vec3& target, const vec3& up){
  vec3 forward = Normalized(target - position);
  vec3 right = Normalized(Cross(up, forward));
  vec3 newUp = Cross(forward, right);

  return mat4(
    right.x, newUp.x, forward.x , 0.0f,
    right.y, newUp.y, forward.y, 0.0f,
    right.z, newUp.z, forward.z, 0.0f,
    -Dot(right, position), -Dot(newUp, position), -Dot(forward, position), 1.0f
  );
}

mat4 Projection(float fov, float aspect, float zNear, float zFar){
  float tanHalfFov = tanf(DEG2RAD(fov * 0.5f));
  float fovY = 1.0f/ tanHalfFov;
  float fovX = fovY / aspect;

  mat4 result;
  result._11 = fovX;
  result._22 = fovY;
  result._33 = zFar;
  result._34 = 1.0f;
  result._43 = -zNear * result._33;
  result._44 = 0.0f;

  return result;
}
mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar){
  float _11 = 2.0f / (right - left);
  float _22 = 2.0f / (top - bottom);
  float _33 = 1.0f / (zFar - zNear);
  float _41 = (left + right) / (left - right);
  float _42 = (top + bottom) / (bottom - top);
  float _43 = (zNear) / (zNear - zFar);

  return mat4 (
    _11, 0.0f, 0.0f, 0.0f,
    0.0f, _22, 0.0f, 0.0f,
    0.0f, 0.0f, _33, 0.0f,
    _41, _42, _43, 1.0f
  );
}




