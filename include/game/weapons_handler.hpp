#pragma once

#include "../engine/entity_manager.hpp"
#include "raylib.h"
#include "shoot_action.hpp"

namespace lampire {
class WeaponsHandler {
public:
  void HandleWeapons(engine::EntityManager &entityManager,
                     std::vector<ShootAction> actions, float ft) {
    auto entities = entityManager.getEntities();
    for (auto &entity : entities) {
      if (entity->weapon) {
        TraceLog(
            LOG_DEBUG,
            "Subtracting cooldown for weapon: FrameTime %f, current_cd: %f", ft,
            entity->weapon->current_cd);
        entity->weapon->current_cd -= ft;
      }
    }

    for (auto &action : actions) {
      if (action.srcEntity->weapon) {
        if (action.srcEntity->weapon->current_cd <= 0) {
          makeBullet(entityManager, action);
          action.srcEntity->weapon->current_cd =
              action.srcEntity->weapon->fireRate;
        }
      }
    }
  }

private:
  void makeBullet(engine::EntityManager &entityManager,
                  const ShootAction &act) {
    // Todo: bullet spawn position is entity pos top left, need to center
    // before scaling against velocity
    auto sourceCenter =
        act.source.add(engine::getCenter(act.srcEntity->renderable->shape));
    auto velocity = act.dest.direction(sourceCenter);
    auto bullet = entityManager.addEntity(engine::EntityType::Bullet);
    auto shape = engine::Circle(5);
    bullet->transform = std::make_unique<engine::TransformComponent>(
        sourceCenter.add(velocity.scale(25)));
    bullet->renderable =
        std::make_unique<engine::RenderableComponent>(shape, RED);
    bullet->velocity = std::make_unique<engine::VelocityComponent>(velocity);
    bullet->collider = std::make_unique<engine::ColliderComponent>(shape);
    bullet->lifetime = std::make_unique<engine::LifetimeComponent>(3);
    TraceLog(LOG_INFO,
             "Spawning bullet: src(%f, %f), transformedSrc(%f, %f), final "
             "spawn(%f, %f)",
             act.source.x, act.source.y, sourceCenter.x, sourceCenter.y,
             bullet->transform->position.x, bullet->transform->position.y);
  }
};
} // namespace lampire
