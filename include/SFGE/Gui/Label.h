#ifndef LABEL_H
#define LABEL_H
#include <SFML/Graphics/Text.hpp>
#include <SFGE/Core/Node.h>

namespace sfge
{
    /// \brief This class is basically a wrapper for sf::Text with the advantage of being a GuiElement derivative.
    class Label : public Node
    {
        public:
            /// \brief Constructor.
            Label(const std::string& labelText = "", int x = 0, int y = 0);
            virtual ~Label();

            /// \brief Set the position of the label (left-top coordinate)
            void setPosition(int x, int y);

            /// \brief Set the font size of the label.
            void setFontSize(int size);

            /// \brief Set the font of the label.
            void setFont(const sf::Font& font);

            /// \brief Set the text of the label.
            void setText(const std::string& name);

            /// \brief Set the color of the label.
            void setColor(const sf::Color& color);

            /// \brief Set the scale of the label.
            void setScale(float scalex, float scaley);

            /// \brief Set the style of the label
            void setStyle(sf::Text::Style style);

            /// \brief Utility method for centering labels
            void setCenterAsOrigin();

            /// \brief Draw the label.
            virtual void onDraw();

        protected:
            sf::Text text;
            bool centered;
    };

}

#endif // LABEL_H
