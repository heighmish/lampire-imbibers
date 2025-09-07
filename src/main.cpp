#include <raylib.h>

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Lampire Imbibers");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
