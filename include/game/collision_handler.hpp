#pragma once

#include "engine/entity_manager.hpp"  // For EntityVector
#include "engine/event_bus.hpp"

namespace lampire {
class CollisionHandler {
   public:
    void handleCollisions(engine::EntityVector& entities,
                          engine::EventBus& eventBus);
};
}  // namespace lampire
