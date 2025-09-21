#pragma once

#include "engine/event_bus.hpp"
namespace lampire {
class DamageHandler {
   public:
    void registerHandlers(engine::EventBus& eventBus);
};
}  // namespace lampire
