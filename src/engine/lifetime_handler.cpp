#include "engine/lifetime_handler.hpp"
#include "engine/entity.hpp"
#include "engine/entity_manager.hpp"

namespace engine {
void LifetimeHandler::UpdateLifetimes(EntityManager &entityManager, float ft) {
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
} // namespace engine
