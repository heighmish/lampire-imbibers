#pragma once

#include <cstddef>
#include <memory>

#include "engine/collider_component.hpp"
#include "engine/lifetime_component.hpp"
#include "engine/renderable_component.hpp"
#include "engine/transform_component.hpp"
#include "engine/velocity_component.hpp"
#include "entity_types.hpp"
#include "game/ai_component.hpp"
#include "game/damage_component.hpp"
#include "game/health_component.hpp"
#include "game/weapon_component.hpp"

namespace engine {
class Entity {
   public:
    void destroy() { is_alive = false; }
    bool operator==(const Entity& rhs) { return this->m_id == rhs.m_id; }
    EntityType getType() const { return m_tag; }

    std::unique_ptr<VelocityComponent> velocity;
    std::unique_ptr<TransformComponent> transform;
    std::unique_ptr<RenderableComponent> renderable;
    std::unique_ptr<ColliderComponent> collider;
    std::unique_ptr<lampire::AiComponent> ai;
    std::unique_ptr<lampire::WeaponComponent> weapon;
    std::unique_ptr<LifetimeComponent> lifetime;
    std::unique_ptr<lampire::HealthComponent> health;
    std::unique_ptr<lampire::DamageComponent> damage;

    bool is_alive = true;

   private:
    friend class EntityManager;
    explicit Entity(EntityType type, size_t id) : m_id(id), m_tag(type) {}

    const size_t m_id = 0;
    const EntityType m_tag = EntityType::Default;
};
}  // namespace engine
