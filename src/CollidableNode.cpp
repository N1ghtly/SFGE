#include "CollidableNode.h"
#include "CollisionDetector.h"

namespace sfge
{

    CollidableNode::CollidableNode(std::string name, bool dynamic) : Node(name), dynamic(dynamic), cd(NULL), removeMarked(false)
    {
        //ctor
    }

    CollidableNode::~CollidableNode()
    {
        if(cd)
            cd->remove(this);
    }

    ConvexShape& CollidableNode::getShape()
    {
        return shape;
    }

    bool CollidableNode::isDynamic()
    {
        return dynamic;
    }

    bool CollidableNode::shouldBeRemoved()
    {
        return removeMarked;
    }

    void CollidableNode::markForRemoval()
    {
        removeMarked = true;
    }

    void CollidableNode::setCollisionDetector(CollisionDetector* col)
    {
        cd = col;
    }

}
