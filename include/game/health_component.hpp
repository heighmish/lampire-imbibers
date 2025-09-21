#pragma once
#include "engine/component.hpp"
namespace lampire {
class HealthComponent : engine::Component {
   public:
    float maxHealth;
    float currentHealth;
    HealthComponent(float max, float current)
        : maxHealth(max), currentHealth(current) {}

    HealthComponent(float max) : maxHealth(max), currentHealth(max) {}
};
}  // namespace lampire
