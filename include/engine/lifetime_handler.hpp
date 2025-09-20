#pragma once

namespace engine {
class EntityManager;

class LifetimeHandler {
public:
  void UpdateLifetimes(EntityManager &entityManager, float ft);
};
} // namespace engine