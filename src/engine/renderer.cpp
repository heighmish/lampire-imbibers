#include "engine/renderer.hpp"

#include "engine/entity.hpp"
#include "engine/renderable_component.hpp"
#include "engine/shapes.hpp"
#include "engine/transform_component.hpp"
#include "raylib.h"
#include <variant>

namespace engine {

void Renderer::renderEntities(EntityVector & entities) {
  for (auto const & entity : entities) {
    if (entity->renderable && entity->transform) {
      drawShape(*entity->renderable, *entity->transform);
    }
  }
}

void Renderer::drawPauseScreen() {
  auto heading = "Game is paused";
  auto fontSize = 40;
  auto centerX = centerTextX(heading, fontSize, GetScreenWidth() / 2);
  DrawText(heading, centerX, GetScreenHeight() / 2, fontSize, WHITE);

  auto subHeading = "Press \"p\" to unpause";
  auto subHeadingFontSize = 20;
  auto subHeadingX =
      centerTextX(subHeading, subHeadingFontSize, GetScreenWidth() / 2);
  DrawText(subHeading, subHeadingX, (GetScreenHeight() / 2) + 50,
           subHeadingFontSize, WHITE);
}

int Renderer::centerTextX(const char *text, int fontSize, int x) {
  auto textLength = MeasureText(text, fontSize);
  return x - (textLength / 2);
}

void Renderer::drawShape(const RenderableComponent &renderable,
               const TransformComponent &transform) {
  std::visit(overloads{[&](const engine::Rect &r) {
                         drawRect(r, transform, renderable.colour);
                       },
                       [&](const engine::Circle &c) {
                         drawCircle(c, transform, renderable.colour);
                       }},
             renderable.shape);
}

void Renderer::drawRect(const Rect &r, const TransformComponent &transform,
              Color colour) {
  DrawRectangle(transform.position.x, transform.position.y, r.width, r.height,
                colour);
}

void Renderer::drawCircle(const Circle &c, const TransformComponent &transform,
                Color colour) {
  DrawCircle(transform.position.x + c.radius, transform.position.y + c.radius,
             c.radius, colour);
}

} // namespace engine
