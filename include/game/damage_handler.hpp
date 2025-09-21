#pragma once

#include "engine/entity_manager.hpp"
#include "engine/event_bus.hpp"
namespace lampire {
class DamageHandler {
   public:
    void registerHandlers(engine::EventBus& eventBus);
    void updateTimers(engine::EntityManager& entityManager, float dt);
};
}  // namespace lampire
