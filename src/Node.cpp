#include <SFGE/Core/Node.h>
#include <algorithm>
#include <SFGE/Util/FileLogger.h>

namespace sfge
{
    bool sortByZValue(const Node* a, const Node* b)
    {
        return (a->getZ() < b->getZ());

    }

    Node::Node(const std::string& name) : parent(NULL), window(NULL), name(name), z(0)
    {
        //ctor
    }

    Node::~Node()
    {
        for(Node* node : children)
        {
            FileLogger::log("deleting node: " + node->getName());
            delete node;
        }
    }

    std::string Node::getName()
    {
        return name;
    }

    void Node::setName(const std::string& name)
    {
        this->name = name;
    }

    void Node::setZ(int z)
    {
        this->z = z;
    }

    int Node::getZ() const
    {
        return z;
    }

    void Node::setWindow(sf::RenderWindow* window)
    {
        this->window = window;
        for(Node* node : children)
            node->setWindow(window);
        onWindowSet();
    }

    void Node::draw()
    {
        onDraw();
        for(Node* node : children)
            node->draw();
    }

    void Node::update(sf::Time delta)
    {
        onUpdate(delta);
        for(Node* node : children)
            node->update(delta);
    }

    void Node::handle(const sf::Event& event)
    {
        onHandle(event);
        for(Node* node : children)
            node->handle(event);
    }

    void Node::addNode(Node* node)
    {
        node->setParent(this);
        node->setWindow(window);
        children.push_back(node);
        std::sort(begin(children), end(children), sortByZValue);
    }

    void Node::removeNode(Node* node)
    {
        for(auto itr = children.begin(); itr != children.end(); itr++)
        {
            if(node == (*itr))
            {
                children.erase(itr);
                return;
            }
        }
    }

    Node* Node::getParent()
    {
        return parent;
    }

    void Node::setParent(Node* parentnode)
    {
        parent = parentnode;
    }

    std::vector<Node*>& Node::getChildren()
    {
        return children;
    }

}
