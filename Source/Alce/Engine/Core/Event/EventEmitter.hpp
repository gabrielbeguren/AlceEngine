#ifndef EVENTEMITTER_HPP
#define EVENTEMITTER_HPP

#include "Event.hpp"
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

namespace alce
{
    class EventEmitter 
    {
    public:
        using Listener = std::function<void(const Event&)>;

        void addListener(const std::string& type, Listener listener) 
        {
            listeners[type].push_back(listener);
        }

        void emitEvent(const Event& event) 
        {
            auto& eventListeners = listeners[event.getType()];
            for (const auto& listener : eventListeners) 
            {
                listener(event);
            }
        }

    private:
        std::unordered_map<std::string, std::vector<Listener>> listeners;
    };

    typedef std::shared_ptr<EventEmitter> EventEmitterPtr;
}

#endif 
