#pragma once

#include "component.hpp"
#include "raylib.h"
#include "shapes.hpp"
namespace engine {
class RenderableComponent : public Component {
   public:
    RenderableComponent(Shape shapeIn, Color colourIn)
        : shape(shapeIn), colour(colourIn) {};
    Shape shape;
    Color colour;
};
}  // namespace engine
