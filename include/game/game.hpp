#pragma once

#include "../engine/entity_manager.hpp"
#include "../game/input_handler.hpp"
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
};
} // namespace lampire
