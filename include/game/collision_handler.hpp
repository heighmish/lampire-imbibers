#pragma once

#include "../engine/entity.hpp"
#include "../engine/entity_manager.hpp"
#include "../engine/shapes.hpp"
#include "raylib.h"
#include <variant>

namespace lampire {
class CollisionHandler {
public:
  void HandleCollisions(engine::EntityVector &entities) {
    for (auto &outerEntity : entities) {
      for (auto &innerEntity : entities) {
        if (outerEntity == innerEntity) {
          continue;
        }
        if (outerEntity->getType() == engine::Player) {
          if (IsColliding(*innerEntity, *outerEntity)) {
            TraceLog(LOG_INFO, "Collision detected with player");
            innerEntity->destroy();
          }
        }
      }
    }
  }

private:
  bool IsColliding(engine::Entity const &Lhs, engine::Entity const &Rhs) {
    return std::visit(
        engine::overloads{[this, &Lhs, &Rhs](const engine::Circle &lhsCircle,
                                             const engine::Circle &rhsCircle) {
                            return checkCollision(lhsCircle, *Lhs.transform,
                                                  rhsCircle, *Rhs.transform);
                          },
                          [this, &Lhs, &Rhs](const engine::Rect &lhsRect,
                                             const engine::Rect &rhsRect) {
                            return checkCollision(lhsRect, *Lhs.transform,
                                                  rhsRect, *Rhs.transform);
                          },
                          [this, &Lhs, &Rhs](const engine::Circle &lhsCircle,
                                             const engine::Rect &rhsRect) {
                            return checkCollision(lhsCircle, *Lhs.transform,
                                                  rhsRect, *Rhs.transform);
                          },
                          [this, &Lhs, &Rhs](const engine::Rect &lhsRect,
                                             const engine::Circle &rhsCircle) {
                            return checkCollision(rhsCircle, *Rhs.transform,
                                                  lhsRect, *Lhs.transform);
                          }},
        Lhs.collider->shape, Rhs.collider->shape);
  }

  bool checkCollision(const engine::Circle &circle,
                      const engine::TransformComponent &circleTransform,
                      const engine::Rect &rectangle,
                      const engine::TransformComponent &rectangleTransform) {
    return CheckCollisionCircleRec(
        Vector2(circleTransform.position.x + circle.radius,
                circleTransform.position.y + circle.radius),
        circle.radius,
        Rectangle{.x = rectangleTransform.position.x,
                  .y = rectangleTransform.position.y,
                  .width = rectangle.width,
                  .height = rectangle.height});
  }

  bool checkCollision(const engine::Circle &circleLeft,
                      const engine::TransformComponent &circleLeftTransform,
                      const engine::Circle &circleRight,
                      const engine::TransformComponent &circleRightTransform) {}

  bool
  checkCollision(const engine::Rect &rectangleLeft,
                 const engine::TransformComponent &rectangleLeftTransform,
                 const engine::Rect &rectangleRight,
                 const engine::TransformComponent &rectangleRightTransform) {}
};

} // namespace lampire
