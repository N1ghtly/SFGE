#include <SFGE/Core/AnimatedSprite.h>

namespace sfge
{
    AnimatedSprite::AnimatedSprite() : currentAnimation(""), looping(false)
    {
        //ctor
    }

    AnimatedSprite::~AnimatedSprite()
    {
        //dtor
    }

    void AnimatedSprite::addAnimation(const std::string& name, Animation animation)
    {
        animations[name] = animation;
    }

    void AnimatedSprite::removeAnimation(const std::string& name)
    {
        auto pos = animations.find(name);
        if(pos != animations.end())
            animations.erase(pos);
    }

    void AnimatedSprite::playAnimation(const std::string& name, bool loop)
    {
        if(animations.find(name) != animations.end())
        {
            currentAnimation = name;
            looping = loop;
        }
    }

    void AnimatedSprite::stopAnimation()
    {
        currentAnimation = "";
    }

    bool AnimatedSprite::isAnimationPlaying()
    {
        return (!currentAnimation.empty());
    }

    std::string AnimatedSprite::getCurrentAnimationName()
    {
        return currentAnimation;
    }

    void AnimatedSprite::update(sf::Time frameTime)
    {
        if(!currentAnimation.empty()) //Are we actually running an animation?
        {
            if(!animations[currentAnimation].update(frameTime) && !looping) //If the animation is finished and we are not looping, stop the animation.
                currentAnimation = "";
            else //Else we just update our subrect
                setTextureRect(animations[currentAnimation].getCurrentFrame());
        }
    }
}
