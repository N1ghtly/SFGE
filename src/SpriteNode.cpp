#include <SFGE/Core/SpriteNode.h>

namespace sfge
{
    SpriteNode::SpriteNode(const std::string& name) : Node(name)
    {
        //ctor
    }

    SpriteNode::SpriteNode(const std::string& name, const std::string& file) : Node(name)
    {
        loadFile(file);
    }

    SpriteNode::~SpriteNode()
    {
        //dtor
    }

    void SpriteNode::setCenterAsOrigin()
    {
        setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    }

    void SpriteNode::loadFile(const std::string& file)
    {
        setTexture(ResourceManager::instance()->getTexture(file));
    }

    void SpriteNode::onDraw()
    {
        window->draw(*this);
    }
}
