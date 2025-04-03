#include "raylib.h"
#include "Geometry2D.h"
#include <iostream>

int main(){

  const int winWidth{920};
  const int winHeight{640};
  InitWindow(winWidth, winHeight, "Test");


  SetTargetFPS(60);

  Circle c1 = Circle(vec2(winWidth/2, winHeight/2), 20);
  Circle c2 = Circle(vec2(winWidth/4, winHeight/4), 30);

  while(!WindowShouldClose()){
    BeginDrawing();
    DrawCircle(c1.position.x, c1.position.y, c1.radius, RED);
    DrawCircle(c2.position.x, c2.position.y, c1.radius, BLUE);
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
