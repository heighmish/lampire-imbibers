#pragma once

#include "entity.hpp"
#include "entity_types.hpp"
#include <cstddef>
#include <memory>
#include <ranges>
#include <vector>
namespace engine {
typedef std::vector<std::shared_ptr<Entity>> EntityVector;
class EntityManager {
public:
  EntityManager() = default;
  ~EntityManager() = default;
  void update();
  EntityVector &getEntities();
  std::ranges::view auto getEntities(EntityType type) {
    return m_entities |
           std::ranges::views::filter([type](std::shared_ptr<Entity> entity) {
             return entity->m_tag == type;
           });
  }
  std::shared_ptr<Entity> addEntity(EntityType type);

private:
  EntityVector m_entities;
  size_t m_created_entities;
  EntityVector m_entities_to_add;
};
} // namespace engine
