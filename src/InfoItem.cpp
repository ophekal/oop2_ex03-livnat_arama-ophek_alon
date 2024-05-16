
#include "InfoItem.h"
#include <string.h>
#include "HandleResources.h"
#include <SFML/Graphics.hpp>

//---------------------------------------------------------------------------------------
InfoItem::InfoItem()
    :m_rectangle(sf::Vector2f(400.f, 100.f))
{
    m_text.setFont(*HandleResources::instance().getFont());
}

//---------------------------------------------------------------------------------------
void InfoItem::updateInfoItem(const sf::Texture& background, float x, float y,
                              const sf::Vector2f size)
{
    m_rectangle.setSize(size);
    m_rectangle.setPosition(x, y);
    m_rectangle.setTexture(&background);
}

//---------------------------------------------------------------------------------------
void InfoItem::printInfoItem(sf::RenderWindow& window) const
{
    window.draw(m_rectangle);
    window.draw(m_text);
}

//---------------------------------------------------------------------------------------
sf::RectangleShape& InfoItem::getRectangleInfoItem()
{
    return m_rectangle;
}

//---------------------------------------------------------------------------------------
void InfoItem::setText(const std::string& text)
{
    m_text.setString(text);
    m_text.setCharacterSize(INFOBAR_TEXT_SIZE);
    m_text.setFillColor(sf::Color::Black);

    //Set the position of the text to be centered within the rectangle
    sf::FloatRect textBounds = m_text.getLocalBounds();
    float textX = m_rectangle.getPosition().x + (m_rectangle.getSize().x - textBounds.width) / 2;
    float textY = m_rectangle.getPosition().y + (m_rectangle.getSize().y - textBounds.height) / 2;
    m_text.setPosition(textX, textY);
}