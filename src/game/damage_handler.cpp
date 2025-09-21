#include "game/damage_handler.hpp"

#include <memory>

#include "engine/action.hpp"
#include "engine/collision_event.hpp"
#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/event_bus.hpp"
#include "game/game_over_event.hpp"

namespace lampire {
void DamageHandler::registerHandlers(engine::EventBus& eventBus) {
    eventBus.subscribe("collision", [&eventBus](
                                        std::unique_ptr<engine::Action> act) {
        if (auto collisionEvent =
                dynamic_cast<engine::CollisionEvent*>(act.get())) {
            auto e1 = collisionEvent->e1;
            auto e2 = collisionEvent->e2;
            if (e1->health && e2->damage && e1->getType() != e2->getType()) {
                e1->health->tryDamage(e2->damage->damage);
                if (e1->health->currentHealth <= 0) {
                    if (e1->getType() == engine::Player) {
                        eventBus.publishEvent(
                            "gameOver",
                            std::make_unique<
                                GameOverEvent>());  // really this should just
                                                    // publish a death
                                                    // notification and
                                                    // somrthing else should
                                                    // handle it, but seems
                                                    // overboard for this
                    } else {
                        e1->destroy();
                    }
                }
            }

            if (e1->getType() == engine::Bullet &&
                e2->getType() != engine::Player) {
                // Todo: bullet dies if hits anything
                // If I add piercing projectiles would need to handle
                e1->destroy();
            }
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
