#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <map>
#include <string>
#include <functional>
#include <queue>
#include <SFGE/Core/Event.h>

#define em sfge::EventManager::instance()

typedef std::function<void (sfge::Event*)> callback;
typedef std::pair<std::string, callback > funcpair;

namespace sfge
{
    /// \brief Class for handling communication between objects
    ///
    /// All hooked functions need to a pointer to sfge::Event.
    /// In the function you should cast it to the correct derived event (if necessary).
    /// This is safe because we KNOW what type of event we're receiving.
    /// It's not totally idiot-proof ofcourse because you can cast it to the wrong derived ^^
    /// @code
    /// void onMouseClicked(sfge::Event* event);
    /// @endcode
    /// When an object whose member function(s) are added to the eventmanager is deleted, the callbacks will be automatically removed.
    /// We do not need a remove function because of this.
    class EventManager
    {
        public:
            ~EventManager();

            /// \brief Makes sure there is only ONE eventmanager at a time.
            static EventManager* instance();

            /// \brief Sends an event. The listeners will be notified IMMEDIATELY and their callbacks are executed, then the function returns.
            void sendEvent(Event* event);

            /// \brief Posts an event on the queue. The listeners will be notified later on.
            void postEvent(Event* event);

            /// \brief Sends all the events in the queue. Should be called every frame.
            void sendQueuedEvents();

            /// \brief Hook a function to an event.
            void hook(const std::string& name, callback func);

            /// \brief Hook a member function to an event.
            ///
            /// @param func The member function to be hooked
            /// @param object The instance where the member function should be called from.
            ///
            /// Here's a little example:
            /// @code
            /// Exampleclass* object = new Exampleclass;
            /// em->hook("onClick", &Exampleclass::handleClick, object);
            /// @endcode
            template<typename T>
            void hook(const std::string& name, void(T::*func)(Event*), T* object)
            {
                callback cb = std::bind(func, object, std::placeholders::_1);
                hook(name, cb);
            }

        private:
            /// \brief Default constructor.
            EventManager();
            static EventManager* eventManager;
            std::multimap<std::string, std::function<void (Event*)> > events;
            std::queue<Event*> eventQueue;



    };
}

#endif // EVENTMANAGER_H
