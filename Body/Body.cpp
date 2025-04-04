#include "Body.h"

Body::Body(IShape& shape, vec2 velocity, vec2 acceleration, float mass):shape{shape}, velocity{velocity}, acceleration{acceleration}, mass{mass}{};
Body::Body(IShape& shape, float mass):Body(shape, vec2{0,0}, vec2{0,0}, mass){};

void Body::ApplyForce(vec2 force){
  
  acceleration = acceleration +  force * (1/mass);
}

void Body::Update(double dt){
  velocity = velocity + acceleration;
  // position = position + velocity;

  for(int i = 0; i < shape.vertices.size(); ++i){
    shape.vertices[i] = shape.vertices[i] + velocity;
  }

  angularAcceleration = acceleration.x /10.f;
  anglularVelocity += angularAcceleration;
  if(anglularVelocity > 0.1){
    anglularVelocity = 0.1;
  }else if(anglularVelocity < -0.1){
    anglularVelocity = -0.1;
  }
  angle += anglularVelocity;

  acceleration = vec2(0,0);
}

