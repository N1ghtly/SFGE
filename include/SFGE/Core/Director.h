#ifndef DIRECTOR_H
#define DIRECTOR_H
#include <vector>
#include <SFML/Graphics.hpp>

namespace sfge
{
    class State;

    /// \brief This class manages the different states of the game.
    class Director
    {
        public:
            Director(sf::RenderWindow& window);
            ~Director();

            /// \brief Runs the director with the passed state as starting state
            void run(State* state);

            /// \brief Replaces the current state
            void replaceState(State* state);

            /// \brief Push a new state on top of the stack
            void pushState(State* state);

            /// \brief Pop the top state
            void popState();

            /// \brief The timestep for the update function
            void setTimestep(sf::Time timestep);

        private:
            void draw();
            void handle(const sf::Event& event);
            void update();

            void doPop();

            bool running;
            bool shouldPop;

            std::vector<State*> states;

            sf::RenderWindow& window;

            sf::Time accumulator;
            sf::Time timestep;
            sf::Clock frameClock;
    };
}
#endif // DIRECTOR_H
