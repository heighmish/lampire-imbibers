#include "game/input_handler.hpp"

#include <memory>

#include "engine/entity.hpp"
#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/event_bus.hpp"
#include "engine/transform_component.hpp"
#include "engine/vec2.hpp"
#include "engine/velocity_component.hpp"
#include "game/input.hpp"
#include "game/shoot_action.hpp"
#include "raylib.h"

namespace lampire {
constexpr int PLAYER_MOVE_SPEED = 5000;
void InputHandler::handleInputs(engine::EntityManager& entityManager,
                                engine::EventBus& eventBus, double dt,
                                Input inputs) {
    auto players = entityManager.getEntities(engine::EntityType::Player);
    for (auto& player : players) {
        player->velocity->velocity.x = 0;
        player->velocity->velocity.y = 0;
        if (inputs.moveDown) {
            player->velocity->velocity.y = PLAYER_MOVE_SPEED * dt;
        }

        if (inputs.moveUp) {
            player->velocity->velocity.y = -PLAYER_MOVE_SPEED * dt;
        }

        if (inputs.moveLeft) {
            player->velocity->velocity.x = -PLAYER_MOVE_SPEED * dt;
        }

        if (inputs.moveRight) {
            player->velocity->velocity.x = PLAYER_MOVE_SPEED * dt;
        }

        if (inputs.isMouseDown) {
            auto spawnPoint = engine::Vec2(player->transform->position);
            auto action = ShootAction(player, spawnPoint,
                                      engine::Vec2(GetMousePosition()));
            eventBus.publishEvent<ShootAction>(action);
            TraceLog(LOG_DEBUG, "Finished handling mouse movement");
        }
    }
}
}  // namespace lampire
