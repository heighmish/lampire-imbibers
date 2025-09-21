#pragma once

#include "engine/component.hpp"
namespace lampire {
class DamageComponent : public engine::Component {
   public:
    DamageComponent(float damage) : damage(damage) {}
    float damage;
};
}  // namespace lampire
