#ifndef SPRITENODE_H
#define SPRITENODE_H
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Node.h"

namespace sfge
{

    class SpriteNode : public Node, public sf::Sprite
    {
        public:
            SpriteNode(const std::string& name = "Sprite");
            SpriteNode(const std::string& name, const std::string& file);
            virtual ~SpriteNode();

            void loadFile(const std::string& name);
            void setCenterAsOrigin();

        protected:
            virtual void onDraw();
    };

}

#endif // SPRITENODE_H
