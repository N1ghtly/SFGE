#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "Animation.h"
#include <SFML/Graphics.hpp>

namespace sfge
{
    /// \brief A sprite that can be animated by Animation objects.
    class AnimatedSprite : public sf::Sprite
    {
        public:
            /// \brief Default Constructor.
            AnimatedSprite();
            ~AnimatedSprite();

            /// \brief Add an animation to the sprite.
            void addAnimation(const std::string& name, Animation animation);

            /// \brief Remove an animation.
            void removeAnimation(const std::string& name);

            /// \brief Play an animation. Optional looping parameter.
            void playAnimation(const std::string& name, bool loop = false);

            /// \brief Stops the currently running animation.
            void stopAnimation();

            /// \brief Returns true if a animation is currently being played
            bool isAnimationPlaying();

            /// \brief Returns the name of the playing animation
            std::string getCurrentAnimationName();

            /// \brief Updates the sprite. Should be called every frame.
            void update(sf::Time frameTime);

        private:
            std::map<std::string, Animation> animations;
            std::string currentAnimation;
            bool looping;

    };
}
#endif // ANIMATEDSPRITE_H
