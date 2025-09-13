#pragma once

#include "../engine/entity_manager.hpp"
#include "../engine/renderer.hpp"
#include "../game/ai_handler.hpp"
#include "../game/input_handler.hpp"
#include "collision_handler.hpp"
#include "enemy_spawner.hpp"
#include "movement_handler.hpp"

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
};
} // namespace lampire
