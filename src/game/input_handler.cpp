#include "../../include/game/input_handler.hpp"
#include "../../include/engine/entity_manager.hpp"
#include "../../include/engine/entity_types.hpp"
#include "raylib.h"

namespace lampire {
constexpr int PLAYER_MOVE_SPEED = 5;
void InputHandler::HandleInputs(engine::EntityManager &entityManager) {
  auto players = entityManager.getEntities(engine::EntityType::Player);
  for (auto &player : players) {
    player->velocity->velocity.x = 0;
    player->velocity->velocity.y = 0;
    if (IsKeyDown(KEY_DOWN)) {
      player->velocity->velocity.y = PLAYER_MOVE_SPEED;
    }
    if (IsKeyDown(KEY_UP)) {
      player->velocity->velocity.y = -PLAYER_MOVE_SPEED;
    }
    if (IsKeyDown(KEY_LEFT)) {
      player->velocity->velocity.x = -PLAYER_MOVE_SPEED;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      player->velocity->velocity.x = PLAYER_MOVE_SPEED;
    }
  }
}
} // namespace lampire
