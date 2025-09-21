#pragma once

#include <variant>

#include "vec2.hpp"

namespace engine {
template <class... Ts>
struct overloads : Ts... {
    using Ts::operator()...;
};

struct Rect {
    float width, height;
};

struct Circle {
    float radius;
};

using Shape = std::variant<Rect, Circle>;

inline Vec2 getCenter(Shape& shape) {
    if (auto const rect = std::get_if<Rect>(&shape)) {
        return Vec2(rect->width / 2, rect->height / 2);
    }

    if (auto const circle = std::get_if<Circle>(&shape)) {
        return Vec2(circle->radius / 2, circle->radius / 2);
    }

    return Vec2(0, 0);
}

}  // namespace engine
