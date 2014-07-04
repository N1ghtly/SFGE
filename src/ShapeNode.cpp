#include <SFGE/Core/ShapeNode.h>

namespace sfge
{
    ShapeNode::ShapeNode(sf::Shape* shape) : shape(shape)
    {
        //ctor
    }

    ShapeNode::~ShapeNode()
    {
        //dtor
    }

    void ShapeNode::onDraw()
    {
        window->draw(*shape);
    }

    sf::Shape* ShapeNode::getShape()
    {
        return shape;
    }
}
