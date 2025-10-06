#include <memory>

#include "engine/action.hpp"
#include "engine/entity.hpp"

namespace lampire {
class DeathEvent : public engine::Action {
   public:
    DeathEvent(std::shared_ptr<engine::Entity> e) : entity(e) {}
    DeathEvent(std::shared_ptr<engine::Entity> e,
               std::shared_ptr<engine::Entity> causingEntity)
        : entity(e), causingEntity(causingEntity) {}
    std::shared_ptr<engine::Entity> entity;
    std::shared_ptr<engine::Entity> causingEntity;
};
}  // namespace lampire
