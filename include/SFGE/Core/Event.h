#ifndef EVENT_H
#define EVENT_H
#include <string>

namespace sfge
{
    /// \brief The base class where custom events should be derived from.
    ///
    /// This class is not an interface and can be sent as event, yet without any parameters.
    class Event
    {
        public:
            /// \brief Constructor.
            Event(const std::string& name);
            virtual ~Event();

            /// \brief Returns the event name.
            std::string getEventName();

        private:
            std::string name;
    };
}

#endif // EVENT_H
