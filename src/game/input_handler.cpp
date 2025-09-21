#include "game/input_handler.hpp"

#include <memory>

#include "engine/entity.hpp"
#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/transform_component.hpp"
#include "engine/velocity_component.hpp"
#include "raylib.h"

namespace lampire {
constexpr int PLAYER_MOVE_SPEED = 5000;
void InputHandler::HandleInputs(engine::EntityManager& entityManager,
                                std::vector<ShootAction>& actions, double dt,
                                bool& paused) {
    if (IsKeyPressed(KEY_P)) {
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
            actions.push_back(ShootAction(player, spawnPoint,
                                          engine::Vec2(GetMousePosition())));
            TraceLog(LOG_DEBUG, "Finished handling mouse movement");
        }
    }
}
}  // namespace lampire
