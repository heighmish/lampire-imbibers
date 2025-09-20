#pragma once

#include "engine/entity_manager.hpp" // For EntityVector

namespace lampire {
class MovementHandler {
public:
  void updatePosition(engine::EntityVector &entities);
};
} // namespace lampire