#include "game/input_handler.hpp"

#include <memory>

#include "engine/entity.hpp"
#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/event_bus.hpp"
#include "engine/transform_component.hpp"
#include "engine/vec2.hpp"
#include "engine/velocity_component.hpp"
#include "game/shoot_action.hpp"
#include "raylib.h"

namespace lampire {
constexpr int PLAYER_MOVE_SPEED = 5000;
void InputHandler::handleInputs(engine::EntityManager& entityManager,
                                engine::EventBus& eventBus, double dt,
                                bool& paused) {
    if (IsKeyDown(KEY_P)) {
        paused = !paused;
    }

    if (paused) {
        return;
    }

    auto players = entityManager.getEntities(engine::EntityType::Player);
    for (auto& player : players) {
        player->velocity->velocity.x = 0;
        player->velocity->velocity.y = 0;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            player->velocity->velocity.y = PLAYER_MOVE_SPEED * dt;
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
            player->velocity->velocity.y = -PLAYER_MOVE_SPEED * dt;
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player->velocity->velocity.x = -PLAYER_MOVE_SPEED * dt;
        }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player->velocity->velocity.x = PLAYER_MOVE_SPEED * dt;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            auto spawnPoint = engine::Vec2(player->transform->position);
            auto action = ShootAction(player, spawnPoint,
                                      engine::Vec2(GetMousePosition()));
            eventBus.publishEvent<ShootAction>(action);
            TraceLog(LOG_DEBUG, "Finished handling mouse movement");
        }
    }
}
}  // namespace lampire
