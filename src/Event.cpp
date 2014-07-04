#include "Event.h"

namespace sfge
{

    Event::Event(const std::string& name) : name(name)
    {

    }

    Event::~Event()
    {
        //dtor
    }

    std::string Event::getEventName()
    {
        return name;
    }

}
