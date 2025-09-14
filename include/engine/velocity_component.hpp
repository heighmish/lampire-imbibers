
#pragma once

#include "component.hpp"
#include "vec2.hpp"
namespace engine {
class VelocityComponent : public Component {
public:
  VelocityComponent() = default;
  VelocityComponent(int xIn, int yIn) : velocity(xIn, yIn) {}
  VelocityComponent(Vec2 vec) : velocity(vec) {}
  Vec2 velocity;
};
} // namespace engine
