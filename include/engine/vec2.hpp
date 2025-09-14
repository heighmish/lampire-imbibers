#pragma once

#include "raylib.h"
#include <cmath>
namespace engine {
class Vec2 {
public:
  Vec2() = default;
  ~Vec2() = default;
  Vec2(float xIn, float yIn) : x(xIn), y(yIn) {};

  Vec2 add(Vec2 const &rhs) const {
    return Vec2(this->x + rhs.x, this->y + rhs.y);
  }

  Vec2 addValue(float value) { return Vec2(this->x + value, this->y + value); }

  Vec2 subtract(Vec2 const &rhs) const {
    return Vec2(this->x - rhs.x, this->y - rhs.y);
  }

  float length() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
  }

  Vec2 divide(float scalar) const {
    return Vec2(this->x / scalar, this->y / scalar);
  }

  Vec2 normalise() const {
    auto len = this->length();
    if (len <= 1e-6f) {
      return Vec2(0, 0);
    }

    return this->divide(len);
  }

  Vec2 scale(float scalar) const {
    return Vec2(this->x * scalar, this->y * scalar);
  }

  Vec2 direction(Vec2 const &rhs) { return this->subtract(rhs).normalise(); }

  Vector2 asRaylibVec() const { return Vector2{.x = this->x, .y = this->y}; }

  float x, y;
};
} // namespace engine
