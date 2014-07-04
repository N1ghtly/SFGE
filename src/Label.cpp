#include "Label.h"

namespace sfge
{

    Label::Label(const std::string& labelText, int x, int y) : centered(false)
    {
        text.setString(labelText);
        text.setPosition(x, y);
    }

    Label::~Label()
    {
        //dtor
    }

    void Label::setPosition(int x, int y)
    {
        text.setPosition(x, y);
    }

    void Label::onDraw()
    {
        window->draw(text);
    }

    void Label::setScale(float scalex, float scaley)
    {
        text.setScale(scalex, scaley);
    }

    void Label::setText(const std::string& txt)
    {
        text.setString(txt);
        if(centered)
            setCenterAsOrigin();
    }

    void Label::setStyle(sf::Text::Style style)
    {
        text.setStyle(style);
    }

    void Label::setFontSize(int size)
    {
        text.setCharacterSize(size);
    }

    void Label::setFont(const sf::Font& font)
    {
        text.setFont(font);
    }

    void Label::setColor(const sf::Color& color)
    {
        text.setColor(color);
    }

    void Label::setCenterAsOrigin()
    {
        int width = text.getLocalBounds().width;
        int height = text.getLocalBounds().height;
        text.setOrigin(width/2, height/2);
        centered = true;
    }
}
