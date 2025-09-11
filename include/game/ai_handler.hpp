#include "../engine/entity.hpp"
#include <memory>
#include <ranges>

namespace lampire {
class AiHandler {
public:
  void UpdateBehaviour(std::shared_ptr<engine::Entity> const &player,
                       std::ranges::view auto aiEntities) {
    for (auto &entity : aiEntities) {
      if (entity->ai && entity->transform && entity->velocity) {
        if (player->transform->position.x > entity->transform->position.x) {
          entity->velocity->velocity.x = 1;
        } else {
          entity->velocity->velocity.x = -1;
        }

        if (player->transform->position.y > entity->transform->position.y) {
          entity->velocity->velocity.y = 1;
        } else {
          entity->velocity->velocity.y = -1;
        }
      }
    }
  }
};
} // namespace lampire
