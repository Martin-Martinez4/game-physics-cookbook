#ifndef LINEAR_MATH_VECTOR_H_
#define LINEAR_MATH_VECTOR_H_

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
} vec2;


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
} vec3;

vec2 operator+(const vec2& l, const vec2& r);
vec2 operator-(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, float r);
bool operator==(const vec2& l, const vec2& r);
bool operator!=(const vec2& l, const vec2& r);

vec3 operator+(const vec3& l, const vec3& r);
vec3 operator-(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, float r);
bool operator==(const vec3& l, const vec3& r);
bool operator!=(const vec3& l, const vec3& r);



#endif