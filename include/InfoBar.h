#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "InfoItem.h"
#include <string.h>


class InfoBar
{
public:
	InfoBar();
	void printInfoBar(sf::RenderWindow& window)const;
	void updateScore(int score);
	void setInfoBar(int score, bool& musicOn);
	void handleClick(const sf::Vector2f& location, bool& levelOver, bool& musicOn);
	void updateMusic(bool& musicOn);
	void checkMusic(const bool& musicOn);


private:
	sf::RectangleShape m_infoBackground;    // for the background
	std::string m_pickedUpSticks;
	std::string m_freeSticks;
	std::string m_score;
	std::vector<InfoItem> m_infoBar;
};