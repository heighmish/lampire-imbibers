#include "game/weapons_handler.hpp"

#include <memory>
#include <vector>

#include "engine/collider_component.hpp"
#include "engine/entity.hpp"
#include "engine/entity_manager.hpp"
#include "engine/entity_types.hpp"
#include "engine/lifetime_component.hpp"
#include "engine/renderable_component.hpp"
#include "engine/shapes.hpp"
#include "engine/transform_component.hpp"
#include "engine/velocity_component.hpp"
#include "game/shoot_action.hpp"
#include "game/weapon_component.hpp"
#include "raylib.h"

namespace {
void makeBullet(engine::EntityManager& entityManager,
                const lampire::ShootAction& act,
                const lampire::WeaponComponent& weapon) {
    auto sourceCenter =
        act.source.add(engine::getCenter(act.srcEntity->renderable->shape));
    auto velocity = act.dest.direction(sourceCenter);
    auto bullet = entityManager.addEntity(engine::EntityType::Bullet);
    auto shape = engine::Circle(5);
    bullet->transform = std::make_unique<engine::TransformComponent>(
        sourceCenter.add(velocity.scale(25)));
    bullet->renderable =
        std::make_unique<engine::RenderableComponent>(shape, RED);
    bullet->velocity = std::make_unique<engine::VelocityComponent>(
        velocity.scale(weapon.projectileSpeed));
    bullet->collider = std::make_unique<engine::ColliderComponent>(shape);
    bullet->lifetime = std::make_unique<engine::LifetimeComponent>(3);
    TraceLog(LOG_INFO,
             "Spawning bullet: src(%f, %f), transformedSrc(%f, %f), final "
             "spawn(%f, %f)",
             act.source.x, act.source.y, sourceCenter.x, sourceCenter.y,
             bullet->transform->position.x, bullet->transform->position.y);
}
}  // namespace

namespace lampire {

void WeaponsHandler::HandleWeapons(engine::EntityManager& entityManager,
                                   std::vector<ShootAction> actions,
                                   double dt) {
    auto entities = entityManager.getEntities();
    for (auto& entity : entities) {
        if (entity->weapon) {
            TraceLog(
                LOG_DEBUG,
                "Subtracting cooldown for weapon: FrameTime %f, current_cd: %f",
                dt, entity->weapon->currentCd);
            entity->weapon->currentCd -= dt;
        }
    }

    for (auto& action : actions) {
        if (action.srcEntity->weapon) {
            auto& weapon = *action.srcEntity->weapon;
            if (weapon.currentCd <= 0) {
                makeBullet(entityManager, action, weapon);
                weapon.currentCd = weapon.fireRate;
            }
        }
    }
}

}  // namespace lampire
