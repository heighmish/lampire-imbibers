#include "../engine/entity.hpp"
#include "raylib.h"
#include <memory>
#include <ranges>

namespace lampire {
class AiHandler {
public:
  void UpdateBehaviour(std::shared_ptr<engine::Entity> const &player,
                       std::ranges::view auto aiEntities) {
    auto playerShape = std::get<engine::Rect>(player->collider->shape);
    for (auto &entity : aiEntities) {
      if (entity->ai && entity->transform && entity->velocity) {
        auto playerCenter = player->transform->position.add(
            engine::Vec2(playerShape.width / 2, playerShape.height / 2));
        auto diffVec = playerCenter.subtract(entity->transform->position);
        auto dist = diffVec.length();

        auto moveSpeed = 1;
        if (moveSpeed >= dist) {
          entity->transform->position = playerCenter;
        } else {
          auto dir = diffVec.normalise();
          auto step = dir.scale(moveSpeed);
          entity->transform->position = entity->transform->position.add(step);
        }
      }
    }
    TraceLog(LOG_DEBUG, "Finished ai handling");
  }
};
} // namespace lampire
