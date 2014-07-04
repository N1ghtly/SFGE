#ifndef NODE_H
#define NODE_H
#include <SFML/Graphics.hpp>


namespace sfge
{
    class Node
    {
        public:
            Node(const std::string& name = "Node");
            virtual ~Node();

            std::string getName();
            void setName(const std::string& name);

            void draw();
            void update(sf::Time delta);
            void handle(const sf::Event& event);

            void addNode(Node* node);
            void removeNode(Node* node);

            void setWindow(sf::RenderWindow* window);

            int getZ() const;
            void setZ(int z);

            Node* getParent();
            void setParent(Node* parentnode);

            std::vector<Node*>& getChildren();

        protected:
            virtual void onDraw(){}
            virtual void onUpdate(sf::Time delta){}
            virtual void onHandle(const sf::Event& event){}
            virtual void onWindowSet(){}

            Node* parent;
            sf::RenderWindow* window;

        private:
            std::vector<Node*> children;
            std::string name;
            int z;
    };
}

#endif // NODE_H
