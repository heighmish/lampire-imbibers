#pragma once

#include "../engine/entity_manager.hpp"
#include "../engine/entity_types.hpp"
#include "../engine/random_generator.hpp"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <memory>

namespace lampire {
class EnemySpawner {
public:
  void spawnEnemy(engine::EntityManager &entityManager, float frametime) {
    if (m_timeSinceLastSpawn >= 0) {
      m_timeSinceLastSpawn -= frametime;
      return;
    }

    const int xRand = engine::RandomGenerator::getInt(0, GetScreenWidth());

    const int yRand = engine::RandomGenerator::getInt(0, GetScreenHeight());

    auto newEnemy = entityManager.addEntity(engine::Enemy);
    auto enemyShape = engine::Circle(10);
    newEnemy->renderable =
        std::make_unique<engine::RenderableComponent>(enemyShape, BLUE);
    newEnemy->collider =
        std::make_unique<engine::ColliderComponent>(enemyShape);
    newEnemy->transform =
        std::make_unique<engine::TransformComponent>(xRand, yRand);
    newEnemy->velocity = std::make_unique<engine::VelocityComponent>();
    newEnemy->ai = std::make_unique<AiComponent>();
    m_timeSinceLastSpawn = m_spawnTime;
  }

private:
  float m_timeSinceLastSpawn;
  static constexpr float m_spawnTime = 5;
};
} // namespace lampire
