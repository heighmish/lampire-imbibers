#include "../../include/game/input_handler.hpp"
#include "../../include/engine/entity_manager.hpp"
#include "../../include/engine/entity_types.hpp"
#include "raylib.h"
#include <memory>

namespace lampire {
constexpr int PLAYER_MOVE_SPEED = 100;
void InputHandler::HandleInputs(engine::EntityManager &entityManager,
                                float frametime) {
  auto players = entityManager.getEntities(engine::EntityType::Player);
  for (auto &player : players) {
    player->velocity->velocity.x = 0;
    player->velocity->velocity.y = 0;
    if (IsKeyDown(KEY_DOWN)) {
      player->velocity->velocity.y = PLAYER_MOVE_SPEED * frametime;
    }

    if (IsKeyDown(KEY_UP)) {
      player->velocity->velocity.y = -PLAYER_MOVE_SPEED * frametime;
    }

    if (IsKeyDown(KEY_LEFT)) {
      player->velocity->velocity.x = -PLAYER_MOVE_SPEED * frametime;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      player->velocity->velocity.x = PLAYER_MOVE_SPEED * frametime;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      auto mousePos = GetMousePosition();
      auto bullet = entityManager.addEntity(engine::EntityType::Bullet);
      bullet->transform =
          std::make_unique<engine::TransformComponent>(mousePos.x, mousePos.y);
      bullet->renderable = std::make_unique<engine::RenderableComponent>(
          engine::Circle(15), RED);
    }
  }
}
} // namespace lampire
