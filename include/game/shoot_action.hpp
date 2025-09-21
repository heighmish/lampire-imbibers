#pragma once

#include <memory>

#include "../engine/action.hpp"
#include "../engine/entity.hpp"
#include "../engine/vec2.hpp"

namespace lampire {
class ShootAction : public engine::Action {
   public:
    std::shared_ptr<engine::Entity> srcEntity;
    engine::Vec2 source;
    engine::Vec2 dest;
    ShootAction(std::shared_ptr<engine::Entity> entity, engine::Vec2 src,
                engine::Vec2 dest)
        : srcEntity(entity), source(src), dest(dest) {}
};
}  // namespace lampire
