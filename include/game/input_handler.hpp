#include "../engine/entity_manager.hpp"

namespace lampire {
class InputHandler {
public:
  void HandleInputs(engine::EntityManager &entityManager, float frametime);
};
} // namespace lampire
