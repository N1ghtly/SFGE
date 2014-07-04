#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "Node.h"

namespace sfge
{
    class ShapeNode : public Node
    {
        public:
            ShapeNode(sf::Shape* shape);
            virtual ~ShapeNode();

            sf::Shape* getShape();

        protected:
            virtual void onDraw();

        private:
            sf::Shape* shape;
    };
}

#endif // SHAPENODE_H
