#pragma once

#include "../engine/entity_manager.hpp"
#include "../engine/shapes.hpp"
#include "raylib.h"
#include <algorithm>
#include <variant>

namespace lampire {
class MovementHandler {
public:
  void updatePosition(engine::EntityVector &entities) {
    for (auto &entity : entities) {
      if (entity->transform && entity->velocity) {
        entity->transform->position =
            entity->transform->position.add(entity->velocity->velocity);
      }

      if (entity->transform && entity->collider) {
        if (entity->getType() == engine::Player) {

          if (auto const rect =
                  std::get_if<engine::Rect>(&entity->collider->shape)) {
            entity->transform->position.x =
                std::clamp(entity->transform->position.x, static_cast<float>(0),
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
};
} // namespace lampire
