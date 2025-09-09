#pragma once

namespace engine {
class Vec2 {
public:
  Vec2() = default;
  ~Vec2() = default;
  Vec2(float xIn, float yIn) : x(xIn), y(yIn) {};
  Vec2 &add(Vec2 const &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  Vec2 &scale(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  float x, y;
};
} // namespace engine
