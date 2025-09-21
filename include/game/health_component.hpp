#pragma once
#include "engine/component.hpp"
#include "raylib.h"
namespace lampire {
class HealthComponent : engine::Component {
   public:
    float maxHealth;
    float currentHealth;
    float lastDamaged = 0;
    float msDamageTimer = 0.200;
    HealthComponent(float max, float current)
        : maxHealth(max), currentHealth(current) {}

    HealthComponent(float max) : maxHealth(max), currentHealth(max) {}

    void tryDamage(float damage) {
        TraceLog(LOG_DEBUG, "Last damaged: %f", lastDamaged);
        if (lastDamaged >= msDamageTimer) {
            currentHealth -= damage;
            if (currentHealth <= 0) {
                currentHealth = 0;
            }
            lastDamaged = 0;
        }
    }
    void updateTimer(float dt) { lastDamaged += dt; }
};
}  // namespace lampire
