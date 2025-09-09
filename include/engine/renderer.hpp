#include "entity_manager.hpp"
#include "raylib.h"
#include "renderable_component.hpp"
#include "shapes.hpp"
#include "transform_component.hpp"
#include <variant>
namespace engine {
class Renderer {

public:
  void renderEntities(EntityVector &entities) {
    for (auto const &entity : entities) {
      if (entity->renderable && entity->transform) {
        drawShape(*entity->renderable, *entity->transform);
      }
    }
  }

private:
  void drawShape(const RenderableComponent &renderable,
                 const TransformComponent &transform) {
    std::visit(overloads{[&](const engine::Rect &r) {
                           drawRect(r, transform, renderable.colour);
                         },
                         [&](const engine::Circle &c) {
                           drawCircle(c, transform, renderable.colour);
                         }},
               renderable.shape);
  }

  void drawRect(const Rect &r, const TransformComponent &transform,
                Color colour) {
    DrawRectangle(transform.position.x, transform.position.y, r.width, r.height,
                  colour);
  }

  void drawCircle(const Circle &c, const TransformComponent &transform,
                  Color colour) {
    DrawCircle(transform.position.x, transform.position.y, c.radius, colour);
  }
};
} // namespace engine
