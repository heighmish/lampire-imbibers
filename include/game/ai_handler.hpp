#pragma once
#include <memory>
#include <ranges>

#include "engine/collider_component.hpp"
#include "engine/entity.hpp"
#include "engine/shapes.hpp"
#include "engine/transform_component.hpp"
#include "engine/vec2.hpp"
#include "raylib.h"

namespace lampire {
class AiHandler {
   public:
    void UpdateBehaviour(std::shared_ptr<engine::Entity> const& player,
                         std::ranges::view auto aiEntities) {
        auto playerShape = std::get<engine::Rect>(player->collider->shape);
        for (auto& entity : aiEntities) {
            if (entity->ai && entity->transform && entity->velocity) {
                auto playerCenter =
                    player->transform->position.add(engine::Vec2(
                        playerShape.width / 2, playerShape.height / 2));
                auto diffVec =
                    playerCenter.subtract(entity->transform->position);
                auto dist = diffVec.length();

                auto dir = diffVec.normalise();
                auto step = dir.scale(m_movespeed);
                entity->velocity->velocity = step;
            }
        }
        TraceLog(LOG_DEBUG, "Finished ai handling");
    }

   private:
    const int m_movespeed = 100;
};
}  // namespace lampire
