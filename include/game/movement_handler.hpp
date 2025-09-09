#pragma once

#include "../engine/entity_manager.hpp"
#include "raylib.h"
#include <algorithm>

namespace lampire {
class MovementHandler {
public:
  void updatePosition(engine::EntityVector &entities) {
    for (auto &entity : entities) {
      if (entity->transform && entity->velocity) {
        entity->transform->position.add(entity->velocity->velocity);

        // Todo: Clamping needs bounding box as well
        entity->transform->position.x =
            std::clamp(entity->transform->position.x, static_cast<float>(0),
                       static_cast<float>(GetScreenWidth()));

        entity->transform->position.y =
            std::clamp(entity->transform->position.y, static_cast<float>(0),
                       static_cast<float>(GetScreenHeight()));
      }
    }
  }
};
} // namespace lampire
