#include "../../include/game/input_handler.hpp"
#include "../../include/engine/entity_manager.hpp"
#include "../../include/engine/entity_types.hpp"
#include "raylib.h"

namespace lampire {
void InputHandler::HandleInputs(engine::EntityManager &entityManager) {
  auto players = entityManager.getEntities(engine::EntityType::Player);
  for (auto &player : players) {
    player->velocity->velocity.x = 0;
    player->velocity->velocity.y = 0;
    if (IsKeyDown(KEY_DOWN)) {
      player->velocity->velocity.y = 1;
    }
    if (IsKeyDown(KEY_UP)) {
      player->velocity->velocity.y = -1;
    }
    if (IsKeyDown(KEY_LEFT)) {
      player->velocity->velocity.x = -1;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      player->velocity->velocity.x = 1;
    }
  }
}
} // namespace lampire
