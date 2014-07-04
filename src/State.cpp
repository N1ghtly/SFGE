#include "State.h"

namespace sfge
{
    State::State() : Node("State")
    {
        setZ(-1000);
    }

    void State::setDirector(Director* director)
    {
        this->director = director;
    }
}
