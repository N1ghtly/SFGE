#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace sfge
{
    /// \brief A class that stores animation data.
    class Animation
    {
        friend class AnimatedSprite;

        public:
            /// \brief Constructor.
            Animation(sf::Time duration = sf::Time::Zero);
            ~Animation();

            /// \brief Sets the duration of the animation.
            void setDuration(sf::Time duration);

            /// \brief Add a frame to the animation.
            ///
            /// A frame is actually just an IntRect object which specifies the subrectangle of the texture.
            void addFrame(sf::IntRect rect);

        private:
            sf::IntRect getCurrentFrame();
            bool update(sf::Time frametime);
            void reset();


            sf::Time duration;
            sf::Time passedTime;
            std::vector<sf::IntRect> frames;
            unsigned currentFrame;
    };
}

#endif // ANIMATION_H
