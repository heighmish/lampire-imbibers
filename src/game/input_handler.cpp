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
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
      player->velocity->velocity.y = PLAYER_MOVE_SPEED * frametime;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
      player->velocity->velocity.y = -PLAYER_MOVE_SPEED * frametime;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
      player->velocity->velocity.x = -PLAYER_MOVE_SPEED * frametime;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
      player->velocity->velocity.x = PLAYER_MOVE_SPEED * frametime;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      auto mousePos = GetMousePosition();
      auto destPoint = engine::Vec2(mousePos.x, mousePos.y);
      auto spawnPoint = engine::Vec2(player->transform->position);
      auto velocity = destPoint.direction(spawnPoint);
      auto bullet = entityManager.addEntity(engine::EntityType::Bullet);
      auto shape = engine::Circle(5);
      bullet->transform = std::make_unique<engine::TransformComponent>(
          spawnPoint.add(velocity.scale(50)));
      bullet->renderable =
          std::make_unique<engine::RenderableComponent>(shape, RED);
      bullet->velocity = std::make_unique<engine::VelocityComponent>(velocity);
      bullet->collider = std::make_unique<engine::ColliderComponent>(shape);
      TraceLog(LOG_DEBUG, "Finished handling mouse movement");
    }
  }
}
} // namespace lampire
