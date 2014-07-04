#ifndef CONVEXCOLLISIONDETECTOR_H
#define CONVEXCOLLISIONDETECTOR_H
#include <set>
#include <SFML/Graphics.hpp>

namespace sfge
{
    class CollidableNode;
    /// \brief A class able to detect collisions between objects derived from CollidableNode
    class CollisionDetector
    {
        public:
            /// \brief Constructor.
            /// \param boundaries The boundaries of the game world. Only objects within this space can be added.
            /// \param cellSize The size of the cells for the grid. (A good size is usually 2x the size of your average game object).\nYou can tune this parameter to improve performance
            CollisionDetector(sf::FloatRect boundaries, int cellSize);
            ~CollisionDetector();

            /// \brief Adds a new collidable to the object pool.
            void add(CollidableNode* obj);

            /// \brief Removes the object from the pool.
            void remove(CollidableNode* obj);

            /// \brief Detects all collisions between added objects. Should be called every frame/timestep.
            void detectCollisions();

            /// \brief Detect collisions with a specific object. The object does not need to be added.
            void detectCollisionsWithObject(CollidableNode* obj);

            /// \brief Detect Collisions with a point in the 2D space.
            bool detectCollisionsWithPoint(sf::Vector2f point);

            /// \brief Sets the offset of the minimum translation vector. This is useful when you want to push colliding object IE 5 pixels out of the other object. On default the offset is 0.
            void setMTVOffset(float offset);

            void setBounds(sf::FloatRect bounds);


        private:
            std::vector< std::vector< std::set<CollidableNode*> > > buckets;
            std::vector< CollidableNode* > dynamicShapes;
            bool collide(CollidableNode* first, CollidableNode* second, sf::Vector2f& mtv, float& overlap);
            std::set< std::set<CollidableNode*>* > getBuckets(sf::FloatRect rect);
            bool isInDimension(sf::FloatRect rect);
            sf::FloatRect boundaries;
            int cellSize;
            int rows;
            int cols;
            float mtvoffset;

            void updateDynamicShapes();
            void resizeToBounds();


    };

}
#endif // CONVEXCOLLISIONDETECTOR_H
