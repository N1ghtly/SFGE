#ifndef CONVEXSHAPE_H
#define CONVEXSHAPE_H
#include <SFML/Graphics.hpp>

namespace sfge
{

    /// \brief Class representing a convex shape on  a 2D plane.
    ///
    /// All points are relative to the position of the object.
    /// Points should be added in a clock-wise manner.
    class ConvexShape
    {
        public:
            /// \brief Constructor
            ConvexShape(int x = 0, int y = 0);
            ~ConvexShape();

            /// \brief Returns the axis-aligned rectangle containing all the points.
            sf::FloatRect getBounds();

            /// \brief Returns the center of the axis-aligned rectangle containing all the points.
            sf::Vector2f getCenter();

            /// \brief Returns the position of the shape.
            sf::Vector2f getPosition();

            /// \brief Sets the position of the shape.
            void setPosition(sf::Vector2f newpos);

            /// \brief Sets the position of the shape.
            void setPosition(float x, float y);

            /// \brief Moves the shape by the argument vector.
            void move(sf::Vector2f vec);

            /// \brief Moves the shape by the argument vector.
            void move(float x, float y);

            /// \brief Adds a point to the shape. Remember: add your points clock-wise!
            void addPoint(sf::Vector2f point);

            /// \brief Adds a point to the shape. Remember: add your points clock-wise!
            void addPoint(float x, float y);

            /// \brief Builds the shape from a rectangle. Just a convenience function.
            void buildFromRect(sf::FloatRect rect);

            /// \brief Returns a vector with all the points.
            std::vector<sf::Vector2f>& getPoints();

        private:
            std::vector<sf::Vector2f> points;
            sf::Vector2f pos;
            sf::VertexArray vertices;
    };

}
#endif // CONVEXSHAPE_H
