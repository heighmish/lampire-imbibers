#pragma once

#include "entity_manager.hpp"
namespace engine {
class LifetimeHandler {
public:
  void UpdateLifetimes(EntityManager &entityManager, float ft) {
    auto entities = entityManager.getEntities();
    for (auto &entity : entities) {
      if (entity->lifetime) {
        entity->lifetime->ttl -= ft;
        if (entity->lifetime->ttl <= 0) {
          entity->destroy();
        }
      }
    }
  }
};
} // namespace engine
