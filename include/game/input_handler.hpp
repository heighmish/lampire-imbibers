#pragma once

#include "../engine/entity_manager.hpp"
#include "engine/event_bus.hpp"
#include "input.hpp"

namespace lampire {
class InputHandler {
   public:
    void handleInputs(engine::EntityManager& entityManager,
                      engine::EventBus& eventBus, double dt, Input inputs);
};
}  // namespace lampire
