/// Design:
/// Central event system
/// Other systems can subscribe event type handlers
/// Handlers are just functions
/// InputSystem publishes Shoot action
/// Weapon Handler subscribes a function that spawns bullets
/// Actions need to be generic
/// We need a way to store functions for specific event types
/// Lets start with pointers and then maybe try template it
#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "engine/action.hpp"
namespace engine {
class EventBus {
   public:
    void handleEvents();

    template <typename EventType>
    void subscribe(std::function<void(const EventType&)> handler) {
        auto wrapper = [handler](Action* basePtr) {
            auto eventPtr = static_cast<EventType*>(basePtr);
            handler(*eventPtr);
        };
        m_handlers[std::type_index(typeid(EventType))].push_back(wrapper);
    }

    template <typename EventType>
    void publishEvent(EventType event) {
        m_actions.push(std::make_unique<EventType>(std::move(event)));
    }

   private:
    std::unordered_map<std::type_index,
                       std::vector<std::function<void(Action*)>>>
        m_handlers;

    std::queue<std::unique_ptr<Action>> m_actions;
};
}  // namespace engine
