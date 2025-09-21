#pragma once
#include "../engine/component.hpp"

namespace lampire {
class WeaponComponent : public engine::Component {
   public:
    float currentCd;
    float fireRate;
    float damage;
    float projectileSpeed;
    WeaponComponent(float cd, float fr, float damage, float speed)
        : currentCd(cd), fireRate(fr), damage(damage), projectileSpeed(speed) {}
};
}  // namespace lampire
