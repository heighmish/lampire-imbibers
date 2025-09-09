#pragma once

#include <variant>

namespace engine {
template <class... Ts> struct overloads : Ts... {
  using Ts::operator()...;
};

struct Rect {
  float width, height;
};

struct Circle {
  float radius;
};

using Shape = std::variant<Rect, Circle>;
} // namespace engine
