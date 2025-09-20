#include "game/game.hpp"
#include <raylib.h>

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Lampire Imbibers");
  SetTraceLogLevel(LOG_INFO);

  SetTargetFPS(60);
  auto lampireGame = lampire::Game();

  while (!WindowShouldClose()) {
    lampireGame.update();

    BeginDrawing();
    ClearBackground(BLACK);
    lampireGame.render();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
