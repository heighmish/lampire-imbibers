#include "../../include/game/game.hpp"
#include "../../include/engine/entity.hpp"
#include "../../include/engine/entity_types.hpp"
#include "../../include/engine/lifetime_handler.hpp"
#include "../../include/engine/renderable_component.hpp"
#include "../../include/engine/shapes.hpp"
#include "../../include/engine/transform_component.hpp"
#include "../../include/engine/velocity_component.hpp"
#include "raylib.h"
#include <cstddef>
#include <memory>

namespace lampire {
constexpr int PLAYER_WIDTH = 25;
constexpr int PLAYER_HEIGHT = 25;

Game::Game() {
  auto player = m_entityManager.addEntity(engine::Player);
  auto rect = engine::Rect{.height = PLAYER_HEIGHT, .width = PLAYER_WIDTH};
  player->renderable =
      std::make_unique<engine::RenderableComponent>(rect, GREEN);
  player->transform = std::make_unique<engine::TransformComponent>(
      GetScreenWidth() / 2, GetScreenHeight() / 2);
  player->velocity = std::make_unique<engine::VelocityComponent>(0, 0);
  player->collider = std::make_unique<engine::ColliderComponent>(rect);
  player->weapon = std::make_unique<WeaponComponent>(0, 1, 1);
}

void Game::update() {
  auto ft = GetFrameTime();
  m_entityManager.update();

  m_inputHandler.HandleInputs(m_entityManager, m_shootActions, ft);
  auto entities = m_entityManager.getEntities();
  m_aiHandler.UpdateBehaviour(
      m_entityManager.getEntities(engine::Player).front(),
      m_entityManager.getEntities(engine::EntityType::Enemy));
  m_movementSystem.updatePosition(entities);
  m_collisionHandler.HandleCollisions(entities);
  m_weaponsHandler.HandleWeapons(m_entityManager, m_shootActions, ft);

  m_lifetimeHandler.UpdateLifetimes(m_entityManager, ft);
  m_enemySpawner.spawnEnemy(m_entityManager, ft);
  m_shootActions.clear();
}

void Game::render() {
  auto entities = m_entityManager.getEntities();
  m_renderer.renderEntities(entities);
}
void Game::shutdown() {}
} // namespace lampire
