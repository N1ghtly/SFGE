#include <SFGE/Core/ConvexShape.h>

namespace sfge
{

    ConvexShape::ConvexShape(int x, int y) : pos(x, y)
    {
        //ctor
    }

    ConvexShape::~ConvexShape()
    {
        //dtor
    }

    sf::FloatRect ConvexShape::getBounds()
    {
        if(!points.empty())
        {
            float left = points[0].x;
            float top = points[0].y;
            float bottom = points[0].y;
            float right = points[0].x;

            for(int i = 1; i < points.size(); i++)
            {
                if(points[i].x < left)
                    left = points[i].x;
                else if(points[i].x > right)
                    right = points[i].x;

                if(points[i].y < top)
                    top = points[i].y;
                else if(points[i].y > bottom)
                    bottom = points[i].y;
            }

            return sf::FloatRect(left, top, right - left, bottom - top);
        }
        else
            return sf::FloatRect();
    }

    sf::Vector2f ConvexShape::getCenter()
    {
        sf::FloatRect rect = getBounds();
        return sf::Vector2f(rect.left + rect.width/2, rect.top + rect.height/2);
    }

    sf::Vector2f ConvexShape::getPosition()
    {
        return pos;
    }

    void ConvexShape::setPosition(float x, float y)
    {
        setPosition(sf::Vector2f(x, y));
    }

    void ConvexShape::setPosition(sf::Vector2f newpos)
    {
        //first we reset them to the relative position
        for(sf::Vector2f& point : points)
            point -= pos;

        pos = newpos;

        //then we increment with new absolute position
        for(int i = 0; i < points.size(); i++)
            points[i] += pos;

    }

    void ConvexShape::move(sf::Vector2f vec)
    {
        setPosition(pos + vec);
    }

    void ConvexShape::move(float x, float y)
    {
        setPosition(pos.x + x, pos.y + y);
    }

    void ConvexShape::addPoint(float x, float y)
    {
        points.push_back(sf::Vector2f(x + pos.x, y + pos.y));
    }

    void ConvexShape::addPoint(sf::Vector2f point)
    {
        addPoint(point.x, point.y);
    }

    std::vector<sf::Vector2f>& ConvexShape::getPoints()
    {
        return points;
    }

    void ConvexShape::buildFromRect(sf::FloatRect rect)
    {
        addPoint(rect.left, rect.top);
        addPoint(rect.left + rect.width, rect.top);
        addPoint(rect.left + rect.width, rect.top + rect.height);
        addPoint(rect.left, rect.top + rect.height);
    }

}
