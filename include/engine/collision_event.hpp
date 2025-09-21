#pragma once
#include <memory>

#include "engine/action.hpp"
#include "engine/entity.hpp"

namespace engine {
class CollisionEvent : public Action {
   public:
    CollisionEvent() = default;
    ~CollisionEvent() = default;
    CollisionEvent(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
        : e1(e1), e2(e2) {}

    std::shared_ptr<Entity> e1;
    std::shared_ptr<Entity> e2;
};
}  // namespace engine
