#pragma once

#include "component.hpp"
#include "vec2.hpp"

namespace engine {
class TransformComponent : public Component {
public:
  TransformComponent(int xIn, int yIn) : position(xIn, yIn) {}
  Vec2 position;
};
} // namespace engine
