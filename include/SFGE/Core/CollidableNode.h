#ifndef CONVEXCOLLIDABLE_H
#define CONVEXCOLLIDABLE_H
#include "ConvexShape.h"
#include "Node.h"

namespace sfge
{
    class CollisionDetector;
    /// \brief The base class for objects that can be added to a CollisionDetector.
    class CollidableNode : public Node
    {
        friend class CollisionDetector;

        public:
            /// \brief Constructor.
            /// @param name This string is used to distinguish different types of objects.\n
            ///        It's convenient to check what type of object you've collided with.
            /// @param dynamic Wether or not the body moves.
            CollidableNode(std::string name, bool dynamic = true);
            virtual ~CollidableNode();

            /// \brief Returns the shape.
            ConvexShape& getShape();

            /// \brief Returns true if the object is dynamic, otherwise false.
            bool isDynamic();

            /// \brief This marks the object for removal. The collision detector will take care of this.
            void markForRemoval();

            /// \brief Returns wether the object is marked for removal or not.
            bool shouldBeRemoved();

            /// \brief This function is called when a collision occurs.
            /// \param obj The object we've collided with.
            /// \param mtv The Minimum Translation Vector (the shortest way out of the other object).
            virtual void onCollision(CollidableNode* obj, sf::Vector2f mtv){}

        protected:
            ConvexShape shape;
            CollisionDetector* cd;
            /// \brief Function used internally by CollisionDetector.
            void setCollisionDetector(CollisionDetector* col);


        private:
            bool dynamic;
            bool removeMarked;


    };

}
#endif // CONVEXCOLLIDABLE_H
