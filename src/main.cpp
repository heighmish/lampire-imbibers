#include "game/game.hpp"
#include <raylib.h>

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Lampire Imbibers");
  SetTraceLogLevel(LOG_INFO);

  auto lampireGame = lampire::Game();

  const double dt = 1.0 / 60.0;
  double accumulator = 0.0;

  while (!WindowShouldClose()) {
    accumulator += GetFrameTime();

    while (accumulator >= dt) {
      lampireGame.update(dt);
      accumulator -= dt;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    lampireGame.render();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
