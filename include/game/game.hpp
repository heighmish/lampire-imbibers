#pragma once

#include "../engine/entity_manager.hpp"
#include "../engine/lifetime_handler.hpp"
#include "../engine/renderer.hpp"
#include "../game/ai_handler.hpp"
#include "../game/input_handler.hpp"
#include "../game/weapons_handler.hpp"
#include "collision_handler.hpp"
#include "enemy_spawner.hpp"
#include "movement_handler.hpp"
#include <vector>

namespace lampire {
class Game {
public:
  Game();
  ~Game() = default;
  void update();
  void render();
  void shutdown();

private:
  engine::EntityManager m_entityManager;
  MovementHandler m_movementSystem;
  InputHandler m_inputHandler;
  engine::Renderer m_renderer;
  EnemySpawner m_enemySpawner;
  AiHandler m_aiHandler;
  CollisionHandler m_collisionHandler;
  WeaponsHandler m_weaponsHandler;
  engine::LifetimeHandler m_lifetimeHandler;

  std::vector<ShootAction> m_shootActions;
};
} // namespace lampire
