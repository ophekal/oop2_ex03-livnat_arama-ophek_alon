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
	void updateRemovableSticks(int removableSticks);
	void updateSticksPicked(int sticksPicked);
	void updateSticksLeft(int sticksLeft);
	void setInfoBar(int score,int removableSticks, int sticksPicked, int sticksLeft, bool& musicOn);
	void handleClick(const sf::Vector2f& location, bool& levelOver,bool& pressedSave, bool& musicOn);
	void updateMusic(bool& musicOn);
	void checkMusic(const bool& musicOn);



private:
	sf::RectangleShape m_infoBackground;    // for the background
	sf::Text m_text;
	std::string m_sticksPicked;
	std::string m_removableSticks;
	std::string m_sticksLeft;
	std::string m_score;
	std::vector<InfoItem> m_infoBar;
};