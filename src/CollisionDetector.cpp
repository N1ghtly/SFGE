#include <SFGE/Core/CollisionDetector.h>
#include <SFGE/Core/CollidableNode.h>
#include <iostream>


typedef std::vector< std::vector< std::set<sfge::CollidableNode*> > >::iterator iter;

double dotp(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f perp(const sf::Vector2f& vec)
{
    return sf::Vector2f(-vec.y, vec.x);
}

namespace sfge
{

    CollisionDetector::CollisionDetector(sf::FloatRect boundaries, int cellSize) : mtvoffset(0), boundaries(boundaries), cellSize(cellSize)
    {
        resizeToBounds();
    }

    CollisionDetector::~CollisionDetector()
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                for(auto itr = buckets[row][col].begin(); itr != buckets[row][col].end(); itr++)
                {
                    (*itr)->setCollisionDetector(NULL);
                }
            }
        }
    }

    void CollisionDetector::resizeToBounds()
    {
        rows = std::ceil( boundaries.height / cellSize );
        cols = std::ceil( boundaries.width / cellSize );

        buckets.resize(rows);
        for(int i = 0; i < rows; i++)
        {
            buckets[i].resize(cols);
        }
    }

    void CollisionDetector::setBounds(sf::FloatRect bounds)
    {
        boundaries = bounds;
        resizeToBounds();
    }

    void CollisionDetector::add(CollidableNode* obj)
    {
        sf::FloatRect rect = obj->getShape().getBounds();
        if(isInDimension(rect))
        {
             //Tell the object we're using this collision detector
            obj->setCollisionDetector(this);

            //Get the overlapping buckets for the object and add it
            auto bkts = getBuckets(rect);
            for(auto itr = bkts.begin(); itr != bkts.end(); itr++)
                (*itr)->insert(obj);

            if(obj->isDynamic())
                dynamicShapes.push_back(obj);
        }
    }

    void CollisionDetector::remove(CollidableNode* obj)
    {
        if(obj->isDynamic())
        {
            if(std::find(dynamicShapes.begin(), dynamicShapes.end(), obj) != dynamicShapes.end())
                dynamicShapes.erase(std::find(dynamicShapes.begin(), dynamicShapes.end(), obj));
        }

        auto bkts = getBuckets(obj->getShape().getBounds());
        for(auto itr = bkts.begin(); itr != bkts.end(); itr++)
            if((*itr)->find(obj) != (*itr)->end())
                (*itr)->erase(obj);

        obj->setCollisionDetector(NULL);
    }

    void CollisionDetector::detectCollisions()
    {
        updateDynamicShapes();

        float overlap;
        sf::Vector2f mtv;
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                for(auto itr = buckets[row][col].begin(); itr != buckets[row][col].end(); itr++)
                {
                    auto itr2 = itr;
                    itr2++;
                    for(itr2; itr2 != buckets[row][col].end(); itr2++)
                    {
                        //We only need to test moving bodies for collision
                        if((*itr)->isDynamic() || (*itr2)->isDynamic())
                        {
                            if(collide((*itr), (*itr2), mtv, overlap))
                            {
                                (*itr)->onCollision((*itr2), mtv*overlap);
                                (*itr2)->onCollision((*itr), -mtv*overlap);
                            }
                        }
                    }
                }
            }
        }
    }

    void CollisionDetector::updateDynamicShapes()
    {
        //Remove all dynamic nodes
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                auto itr = buckets[row][col].begin();
                while(itr != buckets[row][col].end())
                {
                    if((*itr)->isDynamic())
                    {
                        itr = buckets[row][col].erase(itr);
                    }

                    else
                    {
                        itr++;
                    }
                }
            }
        }

        //re-insert dynamic nodes
        auto itr = dynamicShapes.begin();
        while(itr != dynamicShapes.end())
        {
            if((*itr)->shouldBeRemoved())
            {
                (*itr)->setCollisionDetector(NULL);
                itr = dynamicShapes.erase(itr);
                continue;
            }
            else if(isInDimension((*itr)->getShape().getBounds()))
            {
                auto bkts = getBuckets((*itr)->getShape().getBounds());
                for(auto bucketitr = bkts.begin(); bucketitr != bkts.end(); bucketitr++)
                    (*bucketitr)->insert(*itr);
            }
            itr++;
        }
    }

    void CollisionDetector::detectCollisionsWithObject(CollidableNode* obj)
    {
        float overlap;
        sf::Vector2f mtv;
        //Test with other moving bodies
        auto bkts = getBuckets(obj->getShape().getBounds());
        for(auto itr = bkts.begin(); itr != bkts.end(); itr++)
        {
            for(auto it = (*itr)->begin(); it != (*itr)->end(); it++)
            {
                if(collide((*it), obj, mtv, overlap))
                {
                    (*it)->onCollision(obj, mtv*overlap);
                    obj->onCollision((*it), -mtv*overlap);
                }
            }
        }

    }

    bool CollisionDetector::collide(CollidableNode* first, CollidableNode* second, sf::Vector2f& mtv, float& overlap)
    {
        overlap = 1000;
        ConvexShape& obj1 = first->getShape();
        ConvexShape& obj2 = second->getShape();
        std::vector<sf::Vector2f>& object1 = obj1.getPoints();
        std::vector<sf::Vector2f>& object2 = obj2.getPoints();
        int nume = object1.size();
        for(int i=0; i<nume; i++)
        {
            sf::Vector2f edge = object1[(i+1)%nume] - object1[i];
            sf::Vector2f normal = perp(edge);

            float len = sqrt(normal.x*normal.x + normal.y*normal.y);
            normal.x /= len;
            normal.y /= len;

            double min1 = std::numeric_limits<double>::infinity();
            double min2 = min1;
            double max1 = -std::numeric_limits<double>::infinity();
            double max2 = max1;

            for(int j=0; j<object1.size(); j++)
            {
                double dot = dotp(normal, object1[j]);
                min1 = std::min(min1, dot);
                max1 = std::max(max1, dot);
            }
            for(int j=0; j<object2.size(); j++)
            {
                double dot = dotp(normal, object2[j]);
                min2 = std::min(min2, dot);
                max2 = std::max(max2, dot);
            }

            if(min2 > max1 || min1 > max2)
                return false;
            else
            {
                float x3 = std::max(min1, min2);
                float y3 = std::min(max1, max2);
                float length = std::max(y3, x3) - std::min(x3, y3);
                if(length < overlap)
                {
                    mtv.x = normal.x;
                    mtv.y = normal.y;
                    sf::Vector2f d;
                    d.x = obj1.getCenter().x - obj2.getCenter().x;
                    d.y = obj1.getCenter().y - obj2.getCenter().y;
                    if (dotp(normal, d) < 0)
                    {
                        mtv = -mtv;
                    }
                    overlap = length;
                }
            }
        }

        nume = object2.size();
        for(int i=0; i<nume; i++)
        {
            sf::Vector2f edge = object2[(i+1)%nume] - object2[i];
            sf::Vector2f normal = perp(edge);

            float len = sqrt(normal.x*normal.x + normal.y*normal.y);
            normal.x /= len;
            normal.y /= len;

            double min1 = std::numeric_limits<double>::infinity();
            double min2 = min1;
            double max1 = -std::numeric_limits<double>::infinity();
            double max2 = max1;

            for(int j=0; j<object2.size(); j++)
            {
                double dot = dotp(normal, object2[j]);
                min1 = std::min(min1, dot);
                max1 = std::max(max1, dot);
            }
            for(int j=0; j<object1.size(); j++)
            {
                double dot = dotp(normal, object1[j]);
                min2 = std::min(min2, dot);
                max2 = std::max(max2, dot);
            }

            if(min2 > max1 || min1 > max2)
                return false;
            else
            {
                float x3 = std::max(min1, min2);
                float y3 = std::min(max1, max2);
                float length = std::max(y3, x3) - std::min(x3, y3);
                if(length < overlap)
                {
                    mtv.x = normal.x;
                    mtv.y = normal.y;
                    sf::Vector2f d;
                    d.x = obj2.getCenter().x - obj1.getCenter().x;
                    d.y = obj2.getCenter().y - obj1.getCenter().y;
                    if (dotp(normal, d) > 0)
                    {
                        mtv = -mtv;
                    }
                    overlap = length;
                }
            }
        }

        overlap += mtvoffset;
        return true;

    }

    void CollisionDetector::setMTVOffset(float offset)
    {
        mtvoffset = offset;
    }

    bool CollisionDetector::isInDimension(sf::FloatRect rect)
    {
        return (boundaries.contains(rect.top, rect.left) && boundaries.contains(rect.top + rect.height, rect.left) && boundaries.contains(rect.top, rect.left + rect.width) && boundaries.contains(rect.top + rect.height, rect.left + rect.width));
    }

    bool CollisionDetector::detectCollisionsWithPoint(sf::Vector2f point)
    {
        int row = (point.y - boundaries.left) / cellSize;
        int col = (point.x - boundaries.top) / cellSize;
        if(row >= rows || col >= cols)
            return false;

        for(auto itr = buckets[row][col].begin(); itr != buckets[row][col].end(); itr++)
        {
            auto& points = (*itr)->getShape().getPoints();
            bool inside = true;
            for(int p = 0; p < points.size(); p++)
            {
                sf::Vector2f p1 = points[p];
                sf::Vector2f p2 = points[(p+1) % points.size()];
                sf::Vector2f line = p1 - p2;

                line = perp(line); //get normal
                sf::Vector2f t;
                t.x = point.x - p1.x;
                t.y = point.y - p1.y;
                float result = dotp(line, t);

                if(result > 0)
                {
                    inside = false;
                    break;
                }
            }

            if(inside)
                return true;

        }

        return false;
    }

    std::set< std::set<CollidableNode*>* > CollisionDetector::getBuckets(sf::FloatRect rect)
    {
        std::set< std::set<CollidableNode*>* > bkts;

        int row = rect.top / cellSize;
        int col = rect.left / cellSize;
        if(row < rows && col < cols && row >= 0 && col >= 0)
            bkts.insert(&buckets[row][col]);

        //left-bottom corner
        row = (rect.top + rect.height) / cellSize;
        col = rect.left / cellSize;
        if(row < rows && col < cols && row >= 0 && col >= 0)
            bkts.insert(&buckets[row][col]);

        //right-top corner
        row = rect.top / cellSize;
        col = (rect.left + rect.width) / cellSize;
        if(row < rows && col < cols && row >= 0 && col >= 0)
            bkts.insert(&buckets[row][col]);

        //right-bottom corner
        row = (rect.top + rect.height) / cellSize;
        col = (rect.left + rect.width) / cellSize;
        if(row < rows && col < cols && row >= 0 && col >= 0)
            bkts.insert(&buckets[row][col]);

        return bkts;
    }

}
