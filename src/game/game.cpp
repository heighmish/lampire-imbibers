#include "../../include/game/game.hpp"
#include "../../include/engine/entity.hpp"
#include "../../include/engine/entity_types.hpp"
#include "../../include/engine/shape.hpp"
#include "../../include/engine/transform_component.hpp"
#include "../../include/engine/velocity_component.hpp"
#include "raylib.h"
#include <cstddef>
#include <memory>

namespace lampire {
Game::Game() {
  auto player = m_entityManager.addEntity(engine::Player);
  player->shape = std::make_unique<engine::Shape>(engine::Triangle);
  player->transform = std::make_unique<engine::TransformComponent>(
      GetScreenWidth() / 2, GetScreenHeight() / 2);
  player->velocity = std::make_unique<engine::VelocityComponent>(0, 0);
}

void Game::update() {
  m_entityManager.update();
  m_inputHandler.HandleInputs(m_entityManager);
  auto entities = m_entityManager.getEntities();
  m_movementSystem.updatePosition(entities);
}

void Game::render() {
  auto entities = m_entityManager.getEntities();
  for (auto const &entity : entities) {
    if (entity->transform && entity->shape) {
      auto xPos = entity->transform->position.x;
      auto yPos = entity->transform->position.y;
      if (*entity->shape == engine::Triangle) {
        DrawTriangle(Vector2(xPos, yPos), Vector2(xPos - 5, yPos + 5),
                     Vector2(xPos + 5, yPos + 5), GREEN);
      } else if (*entity->shape == engine::Square) {
        DrawRectangle(xPos, yPos, 5, 5, RED);
      } else if (*entity->shape == engine::Circle) {
        DrawCircle(xPos, yPos, 5, BLUE);
      }
    }
  }
}
void Game::shutdown() {}
} // namespace lampire
