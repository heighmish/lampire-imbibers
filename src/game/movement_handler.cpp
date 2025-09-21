#include "game/movement_handler.hpp"

#include <algorithm>
#include <variant>

#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/shapes.hpp"
#include "raylib.h"

namespace lampire {

void MovementHandler::updatePosition(engine::EntityVector& entities,
                                     double dt) {
    for (auto& entity : entities) {
        if (entity->transform && entity->velocity) {
            entity->transform->position = entity->transform->position.add(
                entity->velocity->velocity.scale(dt));
        }

        if (entity->transform && entity->collider) {
            if (entity->getType() == engine::Player) {
                if (auto const rect =
                        std::get_if<engine::Rect>(&entity->collider->shape)) {
                    entity->transform->position.x = std::clamp(
                        entity->transform->position.x, static_cast<float>(0),
                        static_cast<float>(GetScreenWidth()) - rect->width);

                    entity->transform->position.y = std::clamp(
                        entity->transform->position.y, static_cast<float>(0),
                        static_cast<float>(GetScreenHeight()) - rect->height);
                }

                if (auto const circle =
                        std::get_if<engine::Circle>(&entity->collider->shape)) {
                    entity->transform->position.x = std::clamp(
                        entity->transform->position.x,
                        static_cast<float>(0) + circle->radius,
                        static_cast<float>(GetScreenWidth()) - circle->radius);

                    entity->transform->position.y = std::clamp(
                        entity->transform->position.y,
                        static_cast<float>(0) + circle->radius,
                        static_cast<float>(GetScreenHeight()) - circle->radius);
                }
            }
        }
    }
    TraceLog(LOG_DEBUG, "Finished movement");
}

}  // namespace lampire
