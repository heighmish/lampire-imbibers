#pragma once
#include "../engine/component.hpp"

namespace lampire {
class WeaponComponent : public engine::Component {
public:
  float current_cd;
  float fireRate;
  float damage;
  WeaponComponent(float cd, float fr, float damage)
      : current_cd(cd), fireRate(fr), damage(damage) {}
};
} // namespace lampire
