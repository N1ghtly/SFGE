#include <SFGE/Core/Animation.h>

namespace sfge
{

    Animation::Animation(sf::Time dur) : passedTime(sf::Time::Zero), currentFrame(0)
    {
       duration = dur;
    }

    Animation::~Animation()
    {
        //dtor
    }

    void Animation::setDuration(sf::Time dur)
    {
        duration = dur;
    }

    bool Animation::update(sf::Time frametime)
    {
        passedTime += frametime;

        currentFrame = std::floor((passedTime.asSeconds()/duration.asSeconds()) * (frames.size()-1) + 0.5);

        if(passedTime > duration)
        {
            reset();
            return false;
        }

        return true;

    }

    sf::IntRect Animation::getCurrentFrame()
    {
        return frames[currentFrame];
    }

    void Animation::addFrame(sf::IntRect rect)
    {
        frames.push_back(rect);
    }

    void Animation::reset()
    {
        //currentFrame = 0;
        passedTime = sf::Time::Zero;
    }

}
