#include "EventManager.h"

sfge::EventManager* sfge::EventManager::eventManager = 0;

namespace sfge
{
    EventManager::EventManager()
    {
        //ctor
    }

    EventManager::~EventManager()
    {
        //dtor
    }

    EventManager* EventManager::instance()
    {
        if(eventManager == NULL)
            eventManager = new EventManager;

        return eventManager;
    }

    void EventManager::sendEvent(Event* event)
    {
        auto range = events.equal_range(event->getEventName());
        for(auto it = range.first; it != range.second; it++)
        {
            if((*it).second) //valid target object
                (*it).second(event);
            else //target is corrupt/deleted
                it = events.erase(it);
        }
        delete event;
    }

    void EventManager::postEvent(Event* event)
    {
        eventQueue.push(event);
    }

    void EventManager::sendQueuedEvents()
    {
        while(!eventQueue.empty())
        {
            sendEvent(eventQueue.front());
            eventQueue.pop();
        }
    }

    void EventManager::hook(const std::string& eventName, callback func)
    {
        events.insert(funcpair (eventName, func));
    }
}
