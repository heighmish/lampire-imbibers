#pragma once

#include "component.hpp"
namespace engine {
class LifetimeComponent : public Component {
   public:
    float ttl;
    LifetimeComponent(float ttl) : ttl(ttl) {}
};
}  // namespace engine
