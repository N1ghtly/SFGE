#include <SFGE/Gui/Entry.h>

namespace sfge
{
    Entry::Entry(int x, int y, int w, int h) : Node("entry"), focused(false)
    {
        setSize(w, h);
        setPosition(x, y);
        background.setFillColor(sf::Color::White);
        background.setOutlineColor(sf::Color::Black);
        background.setOutlineThickness(3);
        text.setColor(sf::Color::Black);
        text.setCharacterSize(20);
    }

    Entry::~Entry()
    {
        //dtor
    }

    void Entry::setSize(int w, int h)
    {
        background.setSize(sf::Vector2f(w, h));
    }

    void Entry::setPosition(int x, int y)
    {
        background.setPosition(x, y);
        x += 3;
        y += (static_cast<float>(background.getGlobalBounds().height)/2.f - static_cast<float>(text.getCharacterSize())/2.f);
        text.setPosition(x, y);
    }

    void Entry::setFont(const sf::Font& font)
    {
        text.setFont(font);
    }

    void Entry::setFontSize(int size)
    {
        text.setCharacterSize(size);
    }

    void Entry::onHandle(const sf::Event& event)
    {
        if(focused)
        {
            if(event.type == sf::Event::TextEntered)
                if(event.text.unicode > 0x1f && event.text.unicode != 0x7f) // not a control character?
                {
                    text.setString(text.getString() + sf::String(event.text.unicode));
                    if(text.getGlobalBounds().left + text.getGlobalBounds().width > background.getGlobalBounds().left + background.getGlobalBounds().width)
                        stripLastChar();
                }
            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    stripLastChar();
                }
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(background.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                focused = true;
            else focused = false;
        }

    }

    void Entry::stripLastChar()
    {
        if(!text.getString().isEmpty())
        {
            std::string str = text.getString().toAnsiString();
            str = str.substr(0, str.size() - 1);
            text.setString(sf::String(str));
        }
    }

    void Entry::onDraw()
    {
        window->draw(background);
        window->draw(text);
    }

    std::string Entry::getString()
    {
        return text.getString();
    }
}
