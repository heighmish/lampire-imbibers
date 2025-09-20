#pragma once

namespace engine {
class EntityManager;

class LifetimeHandler {
public:
  void UpdateLifetimes(EntityManager &entityManager, double dt);
};
} // namespace engine
