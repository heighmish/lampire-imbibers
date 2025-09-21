/// Design:
/// Central event system
/// Other systems can subscribe event type handlers
/// Handlers are just functions
/// InputSystem publishes Shoot action
/// Weapon Handler subscribes a function that spawns bullets
/// Actions need to be generic
/// We need a way to store functions for specific event types
/// Lets start with points and then maybe try template it
#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "engine/action.hpp"
namespace engine {
class EventBus {
   public:
    void subscribe(std::string actionName,
                   std::function<void(std::unique_ptr<Action>)> handler);
    void publishEvent(std::string actionName, std::unique_ptr<Action> event);
    void handleEvents();

   private:
    std::unordered_map<
        std::string, std::vector<std::function<void(std::unique_ptr<Action>)>>>
        m_handlers;
    std::vector<std::pair<std::string, std::unique_ptr<Action>>> m_actions;
};
}  // namespace engine
