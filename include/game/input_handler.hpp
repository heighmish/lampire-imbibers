#pragma once

#include "../engine/entity_manager.hpp"
#include "engine/event_bus.hpp"

namespace lampire {
class InputHandler {
   public:
    void handleInputs(engine::EntityManager& entityManager,
                      engine::EventBus& eventBus, double dt, bool& paused);
};
}  // namespace lampire
