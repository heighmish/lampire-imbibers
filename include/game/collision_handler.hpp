#pragma once

#include "../engine/entity.hpp"
#include "../engine/entity_manager.hpp"
#include "../engine/shapes.hpp"
#include "raylib.h"
#include "raymath.h"
#include <variant>

namespace lampire {
class CollisionHandler {
public:
  void HandleCollisions(engine::EntityVector &entities) {
    for (auto &outerEntity : entities) {
      if (!(outerEntity->collider && outerEntity->transform)) {
        continue;
      }

      for (auto &innerEntity : entities) {
        if (outerEntity == innerEntity) {
          continue;
        }

        if (!(innerEntity->collider && innerEntity->transform)) {
          continue;
        }

        if (IsColliding(*innerEntity, *outerEntity)) {
          if (outerEntity->getType() == engine::Enemy &&
              innerEntity->getType() == engine::Enemy) {
            auto distance = outerEntity->transform->position.direction(
                innerEntity->transform->position);
            outerEntity->transform->position =
                outerEntity->transform->position.add(distance);
          }

          if (outerEntity->getType() == engine::Bullet &&
              innerEntity->getType() == engine::Enemy) {
            // Todo: health and bullet damage system
            innerEntity->destroy();
            outerEntity->destroy();
          }

          if (outerEntity->getType() == engine::Player &&
              innerEntity->getType() == engine::Enemy) {
            // Todo: player health and game over screen
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
                      const engine::TransformComponent &circleRightTransform) {
    return CheckCollisionCircles(
        Vector2AddValue(circleLeftTransform.position.asRaylibVec(),
                        circleLeft.radius),
        circleLeft.radius,
        Vector2AddValue(circleRightTransform.position.asRaylibVec(),
                        circleRight.radius),
        circleRight.radius);
  }

  bool
  checkCollision(const engine::Rect &rectangleLeft,
                 const engine::TransformComponent &rectangleLeftTransform,
                 const engine::Rect &rectangleRight,
                 const engine::TransformComponent &rectangleRightTransform) {
    return CheckCollisionRecs(Rectangle{.x = rectangleLeftTransform.position.x,
                                        .y = rectangleLeftTransform.position.y,
                                        .width = rectangleLeft.width,
                                        .height = rectangleLeft.height},
                              Rectangle{.x = rectangleRightTransform.position.x,
                                        .y = rectangleRightTransform.position.y,
                                        .width = rectangleRight.width,
                                        .height = rectangleRight.height}

    );
  }
};

} // namespace lampire
