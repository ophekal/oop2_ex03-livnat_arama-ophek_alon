
#include "Clock.h"
#include "InfoItem.h"
#include "HandleResources.h"
#include <SFML/Graphics.hpp>
#include <string>

//------------------------------------------------------------------------

void Clock::setClock(float levelTime, bool& levelOver)
{
	m_rectangle.updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_TIME), INFO_X, CLOCK_Y, INFO_SIZE);

	levelOver = false;
	m_timer = levelTime;
	m_clock.restart();
}

//-----------------------------------------------------------------------
void Clock::printClock(sf::RenderWindow& window, bool& levelOver)
{
	updateTime(levelOver);
	m_rectangle.setText(m_timeString);
	m_rectangle.printInfoItem(window);
}
//-----------------------------------------------------------------------
sf::Clock Clock::getClock()const
{
	return m_clock;
}
//-----------------------------------------------------------------------
void Clock::updateTime(bool& levelOver)
{
	m_timer -= m_clock.getElapsedTime().asSeconds();
	m_clock.restart();

	if (m_timer < 0)
	{
		levelOver = true;
	}
	int leftMinutes = (int)m_timer / 60;
	int leftSeconds = (int)m_timer % 60;

	std::string minString = leftMinutes < 10 ? "0" + std::to_string(leftMinutes) : std::to_string(leftMinutes);
	std::string secString = leftSeconds < 10 ? "0" + std::to_string(leftSeconds) : std::to_string(leftSeconds);
	m_timeString = minString + ":" + secString;
}
