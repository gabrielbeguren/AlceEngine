#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "Event.hpp"
#include <iostream>
#include <functional>

namespace alce
{
    class Listener 
    {
    public:
        Listener(std::function<void(const Event&)> callback) : callback(callback) 
        {

        }

        void onEvent(const Event& event) 
        {
            callback(event);
        }

    private:
        std::function<void(const Event&)> callback;
    };

    typedef std::shared_ptr<Listener> ListenerPtr;
}

#endif 
