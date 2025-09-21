#pragma once

#include <vector>

// Forward Declarations
namespace engine {
class EntityManager;
}

namespace lampire {
struct ShootAction;

class WeaponsHandler {
   public:
    void HandleWeapons(engine::EntityManager& entityManager,
                       std::vector<ShootAction> actions, double dt);
};
}  // namespace lampire
