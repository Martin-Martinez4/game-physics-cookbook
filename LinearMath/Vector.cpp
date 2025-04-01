#include "Vector.h"
#include <cmath>
#include <cfloat>

vec2::vec2(): x{0.0f}, y{0.0f}{};
vec2::vec2(float _x, float _y): x{_x}, y{_y}{};

std::ostream& operator<<(std::ostream &os, const vec2& v){
  return os << "(" << v.x << ", "<< v.y << ")";
}

vec2 operator+(const vec2& l, const vec2& r){
  return { l.x + r.x, l.y + r.y };
}
vec2 operator-(const vec2& l, const vec2& r){
  return { l.x - r.x, l.y - r.y };
}
vec2 operator*(const vec2& l, const vec2& r){
  return { l.x * r.x, l.y * r.y };
}
vec2 operator*(const vec2& l, float r){
  return { l.x * r, l.y * r };
}

bool operator==(const vec2& l, const vec2& r){
  return CMP(l.x, r.x) && CMP(l.y, r.y);
}
bool operator!=(const vec2& l, const vec2& r){
  return !(l==r);
}

float Dot(const vec2& l, const vec2& r){
  return l.x * r.x + l.y * r.y;
}

float Magnitude(const vec2& v){
  return sqrtf(Dot(v,v));
}
float MagnitudeSq(const vec2& v){
  return Dot(v, v);
}

void Normalize(vec2& v){
  v = v * (1.0f / Magnitude(v));
}
vec2 Normalized(const vec2& v){
  if(v == vec2()){
    return vec2(0,0);
  }
  return  v * (1.0f / Magnitude(v));
}
float Angle(const vec2& l, const vec2& r){
  float m = sqrtf(MagnitudeSq(l) * MagnitudeSq(r));
  return acos(Dot(l, r)/m);
}

vec2 Project(const vec2& length, const vec2& direction){
  return direction * (Dot(length, direction) / MagnitudeSq(direction));
}
vec2 Perpendicular(const vec2& length, const vec2& direction){
  return length - Project(length, direction);
}
vec2 Reflection(const vec2& vec, const vec2& normal){
  return vec - normal * (Dot(vec, normal) * 2.0f);
}



vec3::vec3(): x{0.0f}, y{0.0f}, z{0.0f}{};
vec3::vec3(float _x, float _y, float _z): x{_x}, y{_y}, z{_z}{};

std::ostream& operator<<(std::ostream &os, const vec3& v){
  return os << "vec3(" << v.x << ", "<< v.y << ", "<< v.z << ")";
}

vec3 operator+(const vec3& l, const vec3& r){
  return { l.x + r.x, l.y + r.y, l.z + r.z };
}
vec3 operator-(const vec3& l, const vec3& r){
  return { l.x - r.x, l.y - r.y, l.z - r.z };
}
vec3 operator*(const vec3& l, const vec3& r){
  return { l.x * r.x, l.y * r.y, l.z * r.z };
}
vec3 operator*(const vec3& l, float r){
  return { l.x * r, l.y * r, l.z * r };
}

bool operator==(const vec3& l, const vec3& r){
  return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
}
bool operator!=(const vec3& l, const vec3& r){
  return !(l==r);
}

float Dot(const vec3& l, const vec3& r){
  return l.x * r.x + l.y * r.y + l.z * r.z;
}

float Magnitude(const vec3& v){
  return sqrtf(Dot(v,v));
}
float MagnitudeSq(const vec3& v){
  return Dot(v,v);
}

void Normalize(vec3& v){
  v = v * (1.0f / Magnitude(v));
}
vec3 Normalized(const vec3& v){
  return  v * (1.0f / Magnitude(v));
}

vec3 Cross(const vec3& l, const vec3& r){
  return vec3(l.y*r.z - l.z*r.y, l.z*r.x - l.x*r.z, l.x*r.y - l.y*r.x);
}

float Angle(const vec3& l, const vec3& r){
  float m = sqrtf(MagnitudeSq(l) * MagnitudeSq(r));
  return acos(Dot(l, r)/m);
}

vec3 Project(const vec3& length, const vec3& direction){
  return direction * (Dot(length, direction) / MagnitudeSq(direction));
}
vec3 Perpendicular(const vec3& length, const vec3& direction){
  return length - Project(length, direction);
}
vec3 Reflection(const vec3& vec, const vec3& normal){
  return vec - normal * (Dot(vec, normal) * 2.0f);
}




