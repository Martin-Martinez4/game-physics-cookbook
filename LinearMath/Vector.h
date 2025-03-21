#ifndef LINEAR_MATH_VECTOR_H_
#define LINEAR_MATH_VECTOR_H_
#include "ostream"

const float EPSILON_FLOAT = 0.0001f;
// compare floating point numbers
#define CMP(x, y)(fabs((x)-(y)) <= EPSILON_FLOAT * fmax(1.0f, fmaxf(fabsf(x), fabsf(y))))

#define CLAMP(number, minimum, maximum) number = (number < minimum) ? minimum : ((number > maximum) ? maximum : number)

#define OVERLAP(aMin, aMax, bMin, bMax) ((bMin <= aMax) && (aMin <= bMax))

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)

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

float Angle(const vec2& l, const vec2& r);

vec2 Project(const vec2& length, const vec2& direction);
vec2 Perpendicular(const vec2& length, const vec2& direction);
vec2 Reflection(const vec2& vec, const vec2& normal);


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

float Angle(const vec3& l, const vec3& r);

vec3 Project(const vec3& length, const vec3& direction);
vec3 Perpendicular(const vec3& length, const vec3& direction);
vec3 Reflection(const vec3& vec, const vec3& normal);

#endif