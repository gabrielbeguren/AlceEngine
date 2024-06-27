#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <memory>

namespace alce
{
    class Event 
    {
    public:
    
        Event(const std::string& type) : type(type) 
        {

        }

        const std::string& getType() const { return type; }

    private:
        std::string type;
    };

    typedef std::shared_ptr<Event> EventPtr;
}

#endif 
