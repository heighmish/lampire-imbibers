#pragma once

#include <vector>

#include "../engine/entity_manager.hpp"
#include "shoot_action.hpp"

namespace lampire {
class InputHandler {
   public:
    void HandleInputs(engine::EntityManager& entityManager,
                      std::vector<ShootAction>& actions, double dt,
                      bool& paused);
};
}  // namespace lampire
