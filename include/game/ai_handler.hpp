#pragma once
#include "engine/entity.hpp"
#include "engine/collider_component.hpp"
#include "engine/shapes.hpp"
#include "engine/transform_component.hpp"
#include "raylib.h"
#include <memory>
#include <ranges>

namespace lampire {
class AiHandler {
public:
  void UpdateBehaviour(std::shared_ptr<engine::Entity> const &player,
                       std::ranges::view auto aiEntities, double dt) {
    auto playerShape = std::get<engine::Rect>(player->collider->shape);
    for (auto &entity : aiEntities) {
      if (entity->ai && entity->transform && entity->velocity) {
        auto playerCenter = player->transform->position.add(
            engine::Vec2(playerShape.width / 2, playerShape.height / 2));
        auto diffVec = playerCenter.subtract(entity->transform->position);
        auto dist = diffVec.length();

        auto moveSpeed = 100; // Note: This should probably be in a component!
        if ((moveSpeed * dt) >= dist) {
          entity->transform->position = playerCenter;
        } else {
          auto dir = diffVec.normalise();
          auto step = dir.scale(moveSpeed * dt);
          entity->transform->position = entity->transform->position.add(step);
        }
      }
    }
    TraceLog(LOG_DEBUG, "Finished ai handling");
  }
};
} // namespace lampire
