#include "LabelButton.h"

namespace sfge
{

    LabelButton::LabelButton(const std::string& labelText, int x, int y) : Label(labelText, x, y)
    {
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    }

    LabelButton::~LabelButton()
    {
        //dtor
    }

    void LabelButton::onHandle(const sf::Event& event)
    {
        switch(event.type)
        {
            case sf::Event::MouseButtonPressed:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f pos(window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)));
                    if(text.getGlobalBounds().contains(pos))
                        if(onClickCallback)
                            onClickCallback();
                }
                break;
            }
            case sf::Event::MouseMoved:
            {
                sf::Vector2f pos(window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)));
                if(text.getGlobalBounds().contains(pos))
                    text.setScale(1.1, 1.1);
                else
                    text.setScale(1.0, 1.0);
            }
            default: break;
        }
    }

}
