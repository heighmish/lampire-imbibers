#include "engine/event_bus.hpp"

#include <typeindex>

namespace engine {

void EventBus::handleEvents() {
    while (!m_actions.empty()) {
        auto& event = m_actions.front();
        auto eventType = std::type_index(typeid(*event));
        auto it = m_handlers.find(eventType);
        if (it != m_handlers.end()) {
            for (auto& handler : it->second) {
                handler(event.get());
            }
        }

        m_actions.pop();
    }
}
}  // namespace engine
