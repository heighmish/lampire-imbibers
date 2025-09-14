#include "../engine/action.hpp"
#include "../engine/entity.hpp"
#include "../engine/vec2.hpp"
#include <memory>

namespace lampire {
class ShootAction : public engine::Action {
public:
  std::shared_ptr<engine::Entity> srcEntity;
  engine::Vec2 source;
  engine::Vec2 dest;
};
} // namespace lampire
