#pragma once

#include "collision_handler.hpp"
#include "enemy_spawner.hpp"
#include "engine/entity_manager.hpp"
#include "engine/event_bus.hpp"
#include "engine/lifetime_handler.hpp"
#include "engine/renderer.hpp"
#include "game/ai_handler.hpp"
#include "game/damage_handler.hpp"
#include "game/input_handler.hpp"
#include "movement_handler.hpp"
#include "weapons_handler.hpp"

namespace lampire {
class Game {
   public:
    Game();
    ~Game() = default;
    void update(double dt);
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
    engine::EventBus m_eventBus;
    DamageHandler m_damageHandler;

    bool m_isPaused = false;
    bool m_isGameOver = false;
};
}  // namespace lampire
