#ifndef LINEAR_MATH_VECTOR_H_
#define LINEAR_MATH_VECTOR_H_
#include "ostream"

typedef struct vec2{
  vec2();
  vec2(float _x, float _y);

  union{
    struct{
      float x;
      float y;
    };

    float asArray[2];
  };

  float& operator[](int i){
    return asArray[i];
  }
  friend std::ostream& operator<<(std::ostream &os, const vec2& v);
} vec2;

vec2 operator+(const vec2& l, const vec2& r);
vec2 operator-(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, float r);
bool operator==(const vec2& l, const vec2& r);
bool operator!=(const vec2& l, const vec2& r);


float Dot(const vec2& l, const vec2& r);

float Magnitude(const vec2& v);
float MagnitudeSq(const vec2& v);

void Normalize(vec2& v);
vec2 Normalized(const vec2& v);

typedef struct vec3{
  vec3();
  vec3(float _x, float _y, float _z);

  union{
    struct{
      float x;
      float y;
      float z;
    };

    float asArray[3];
  };

  float& operator[](int i){
    return asArray[i];
  }
  friend std::ostream& operator<<(std::ostream &os, const vec3& v);

} vec3;

vec3 operator+(const vec3& l, const vec3& r);
vec3 operator-(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, float r);
bool operator==(const vec3& l, const vec3& r);
bool operator!=(const vec3& l, const vec3& r);

float Dot(const vec3& l, const vec3& r);

float Magnitude(const vec3& v);
float MagnitudeSq(const vec3& v);

void Normalize(vec3& v);
vec3 Normalized(const vec3& v);

vec3 Cross(const vec3& l, const vec3& r);


#endif