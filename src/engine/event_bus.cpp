#include "engine/event_bus.hpp"

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "engine/action.hpp"
#include "raylib.h"

namespace engine {
void EventBus::subscribe(std::string actionName,
                         std::function<void(std::unique_ptr<Action>)> handler) {
    TraceLog(LOG_INFO, "Registering handler for action: %s...",
             actionName.c_str());
    if (m_handlers.contains(actionName)) {
        m_handlers[actionName].push_back(handler);
    } else {
        m_handlers[actionName] =
            std::vector<std::function<void(std::unique_ptr<Action>)>>{handler};
    }
}
void EventBus::publishEvent(std::string actionName,
                            std::unique_ptr<Action> event) {
    m_actions.push(std::make_pair(actionName, std::move(event)));
}

void EventBus::handleEvents() {
    while (!m_actions.empty()) {
        auto& [actionName, action] = m_actions.front();
        TraceLog(LOG_INFO, "Handler found for %s, triggering handler",
                 actionName.c_str());
        if (m_handlers.contains(actionName)) {
            for (auto const& func : m_handlers[actionName]) {
                func(std::move(action));
            }
        }
        m_actions.pop();
    }
}
}  // namespace engine
