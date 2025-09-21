#pragma once

#include "engine/entity_manager.hpp"  // For EntityVector

namespace lampire {
class CollisionHandler {
   public:
    void handleCollisions(engine::EntityVector& entities);
};
}  // namespace lampire
