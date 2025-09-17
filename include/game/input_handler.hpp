#pragma once

#include "../engine/entity_manager.hpp"
#include "shoot_action.hpp"
#include <vector>

namespace lampire {
class InputHandler {
public:
  void HandleInputs(engine::EntityManager &entityManager,
                    std::vector<ShootAction> &actions, float frametime,
                    bool &paused);
};
} // namespace lampire
