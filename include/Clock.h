
#pragma once
#include <SFML/Graphics.hpp>
#include "InfoItem.h"
#include <string>

class Clock
{
public:
	Clock() = default;
	void setClock(float levelTime, bool& levelOver);
	void printClock(sf::RenderWindow& window, bool& levelOver);
	sf::Clock getClock()const;
	float getTimer()const;

private:
	void updateTime(bool& levelOver);

	sf::Clock m_clock;
	sf::Time m_setTime;
	float m_timer;
	std::string m_timeString;
	InfoItem m_rectangle;
};