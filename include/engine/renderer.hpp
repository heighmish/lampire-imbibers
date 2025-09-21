#pragma once

#include "engine/entity_manager.hpp"  // For EntityVector
#include "raylib.h"                   // For Color

namespace engine {

// Forward declarations
class RenderableComponent;
class TransformComponent;
struct Rect;
struct Circle;

class Renderer {
   public:
    void renderEntities(EntityVector& entities);
    void drawPauseScreen();
    int centerTextX(const char* text, int fontSize, int x);

   private:
    void drawShape(const RenderableComponent& renderable,
                   const TransformComponent& transform);
    void drawRect(const Rect& r, const TransformComponent& transform,
                  Color colour);
    void drawCircle(const Circle& c, const TransformComponent& transform,
                    Color colour);
};
}  // namespace engine
