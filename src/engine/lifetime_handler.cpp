#include "engine/lifetime_handler.hpp"
#include "engine/entity.hpp"
#include "engine/entity_manager.hpp"

namespace engine {
void LifetimeHandler::UpdateLifetimes(EntityManager &entityManager, double dt) {
  auto entities = entityManager.getEntities();
  for (auto &entity : entities) {
    if (entity->lifetime) {
      entity->lifetime->ttl -= dt;
      if (entity->lifetime->ttl <= 0) {
        entity->destroy();
      }
    }
  }
}
} // namespace engine
