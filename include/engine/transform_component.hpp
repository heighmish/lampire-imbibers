#pragma once

#include "component.hpp"
#include "vec2.hpp"

namespace engine {
class TransformComponent : public Component {
   public:
    TransformComponent(int xIn, int yIn) : position(xIn, yIn) {}
    TransformComponent(Vec2 vec) : position(vec) {}
    Vec2 position;
};
}  // namespace engine
