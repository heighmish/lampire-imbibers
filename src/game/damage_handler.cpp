#include "game/damage_handler.hpp"

#include <memory>

#include "engine/collision_event.hpp"
#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/event_bus.hpp"
#include "game/death_event.hpp"

namespace lampire {
void DamageHandler::registerHandlers(engine::EventBus& eventBus) {
    eventBus.subscribe<engine::CollisionEvent>(
        [&eventBus](engine::CollisionEvent act) {
            auto e1 = act.e1;
            auto e2 = act.e2;
            if (e1->health && e2->damage && e1->getType() != e2->getType()) {
                e1->health->tryDamage(e2->damage->damage);
                if (e1->health->currentHealth <= 0) {
                    if (e1->getType() != engine::Player) {
                        e1->destroy();
                    }

                    eventBus.publishEvent(DeathEvent(e1, e2));
                }
            }

            if (e1->getType() == engine::Bullet &&
                e2->getType() != engine::Player) {
                // Todo: bullet dies if hits anything
                // If I add piercing projectiles would need to handle
                e1->destroy();
            }
        });
}

void DamageHandler::updateTimers(engine::EntityManager& entityManager,
                                 float dt) {
    auto entities = entityManager.getEntities();
    for (auto& entity : entities) {
        if (entity->health) {
            entity->health->updateTimer(dt);
        }
    }
}

}  // namespace lampire
