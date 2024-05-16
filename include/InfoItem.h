#pragma once
#include <SFML/Graphics.hpp>

class InfoItem
{
public:
	InfoItem();
	void updateInfoItem(const sf::Texture& background, float x, float y, const sf::Vector2f size);
	void printInfoItem(sf::RenderWindow& window) const;
	sf::RectangleShape& getRectangleInfoItem();
	void setText(const std::string& text);

private:
	sf::Text m_text;
	sf::RectangleShape m_rectangle;
};