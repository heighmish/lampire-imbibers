#pragma once

#include "engine/entity_manager.hpp"  // For EntityVector

namespace lampire {
class CollisionHandler {
   public:
    void HandleCollisions(engine::EntityVector& entities);
};
}  // namespace lampire
