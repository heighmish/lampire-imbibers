#pragma once

#include "engine/entity_manager.hpp"
#include "engine/event_bus.hpp"

namespace lampire {
struct ShootAction;

class WeaponsHandler {
   public:
    void handleWeapons(engine::EntityManager& entityManager, double dt);
    void registerEvents(engine::EventBus& eventBus,
                        engine::EntityManager& entityManager);
};
}  // namespace lampire
