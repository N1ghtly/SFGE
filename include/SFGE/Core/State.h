#ifndef STATE_H
#define STATE_H
#include "Director.h"
#include "ResourceManager.h"
#include "Node.h"

namespace sfge
{
    /// \brief The base class for states that can be added to a director
    class State : public Node
    {
        friend class Director;

        public:
            /// \brief Constructor
            State();

            virtual ~State(){};

            /// \brief Called when another state is pushed on top of the stack.
            virtual void pause(){};

            /// \brief Called when the state becomes the top of the stack.
            virtual void resume(){};

        protected:
            Director* director;

        private:
            void setDirector(Director* director);
    };
}

#endif // STATE_H
