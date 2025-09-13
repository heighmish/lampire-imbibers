#include "../../include/engine/entity_manager.hpp"
#include "../../include/engine/entity.hpp"
#include <memory>
#include <vector>

namespace engine {
void EntityManager::update() {
  for (auto &entity : m_entities_to_add) {
    m_entities.emplace_back(entity);
  }
  m_entities_to_add.clear();

  std::erase_if(m_entities, [](auto &e) { return !e->is_alive; });
}
EntityVector &EntityManager::getEntities() { return m_entities; }

std::shared_ptr<Entity> EntityManager::addEntity(EntityType type) {
  auto entity = std::shared_ptr<Entity>(new Entity(type, m_created_entities));
  ++m_created_entities;
  m_entities_to_add.push_back(entity);
  return entity;
}
} // namespace engine
