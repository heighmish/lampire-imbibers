#pragma once

#include "entity_types.hpp"
#include "shape.hpp"
#include "transform_component.hpp"
#include "velocity_component.hpp"
#include <cstddef>
#include <memory>

namespace engine {
class Entity {

public:
  void destroy() { is_alive = false; }

  std::unique_ptr<VelocityComponent> velocity;
  std::unique_ptr<TransformComponent> transform;
  std::unique_ptr<Shape> shape;

  bool is_alive = true;

private:
  friend class EntityManager;
  explicit Entity(EntityType type, size_t id) : m_id(id), m_tag(type) {}

  const size_t m_id = 0;
  const EntityType m_tag = EntityType::Default;
};
} // namespace engine
