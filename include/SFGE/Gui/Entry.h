#ifndef ENTRY_H
#define ENTRY_H
#include <SFML/Graphics.hpp>
#include <SFGE/Core/Node.h>

namespace sfge
{
    /// \brief Element for entering text in.
    class Entry : public Node
    {
        public:
            /// \brief Constructor
            Entry(int x = 0, int y = 0, int w = 0, int h = 0);
            virtual ~Entry();

            /// \brief Draw the Entry
            void onDraw();

            /// \brief Handle the event.
            void onHandle(const sf::Event& event);

            /// \brief Set the size of the Entry.
            void setSize(int w, int h);

            /// \brief Set the position of the Entry.
            void setPosition(int x, int y);

            /// \brief Set the font of the entered text.
            void setFont(const sf::Font& font);

            /// \brief Set the font size of the entered text.
            void setFontSize(int size);

            /// \brief Retrieve the entered text.
            std::string getString();

        private:
            void stripLastChar();
            sf::Text text;
            sf::RectangleShape background;
            bool focused;
    };

}

#endif // ENTRY_H
