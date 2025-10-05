#include <memory>

#include "engine/action.hpp"
#include "engine/entity.hpp"

namespace lampire {
class DeathEvent : public engine::Action {
   public:
    DeathEvent(std::shared_ptr<engine::Entity> e) : entity(e) {}
    std::shared_ptr<engine::Entity> entity;
};
}  // namespace lampire
