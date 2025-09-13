#pragma once

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

  Vec2 subtract(Vec2 const &rhs) const {
    return Vec2(this->x - rhs.x, this->y - rhs.y);
  }

  float length() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
  }

  Vec2 normalize() const {
    auto len = this->length();
    if (len <= 1e-6f) {
      return Vec2(0, 0);
    }

    return Vec2(this->x / len, this->y / len);
  }

  Vec2 scale(float scalar) const {
    return Vec2(this->x * scalar, this->y * scalar);
  }

  float x, y;
};
} // namespace engine
