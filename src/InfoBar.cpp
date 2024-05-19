
#include "InfoBar.h"
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "HandleResources.h"

//----------------------------------------------------------------------------------------------------------------------------
InfoBar::InfoBar()
	:m_infoBackground(sf::Vector2f(INFO_WID, INFO_HIG))
{
	m_infoBackground.setPosition({ INFO_START_X ,INFO_START_Y });
	m_infoBackground.setTexture(HandleResources::instance().getBackgroundTexture(B_INFOBAR));

	m_text.setFont(*HandleResources::instance().getFont());
	m_text.setString("Information");
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(75, 50);

	m_infoBar.resize(8);
	m_infoBar[0].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_SAVE), INFO_X, SAVE_Y, INFO_SIZE);
	m_infoBar[1].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
	m_infoBar[2].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_HOME), HOME_X, HOME_Y, SOUND_SIZE);
	m_infoBar[3].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_FREE), INFO_X, FREE_Y, INFO_SIZE);
	m_infoBar[4].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_PICKEDUP), INFO_X, PICKEDUP_Y, INFO_SIZE);
	m_infoBar[5].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_LEFT), INFO_X, LEFT_Y, INFO_SIZE);
	m_infoBar[6].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_SCORE), INFO_X, SCORE_Y, INFO_SIZE);
	m_infoBar[7].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_HINT), INFO_X, HINT_Y, INFO_SIZE);
}

//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::setInfoBar(int score, int removableSticks, int sticksPicked, int sticksLeft, bool& musicOn)
{
	//updateLife(lives);
	updateScore(score);
	updateRemovableSticks(removableSticks);
	updateSticksPicked(sticksPicked);
	updateSticksLeft(sticksLeft);
	//updateKey(key);
	//updateLevel(levelNum);
	checkMusic(musicOn);
}
//-------------------------------------------------------------------------------------------------
void InfoBar::updateRemovableSticks(int removableSticks)
{
	m_removableSticks = std::to_string(removableSticks);
    m_infoBar[3].setText(m_removableSticks);
}
//----------------------------------------------------------------------------------
void InfoBar::updateSticksPicked(int sticksPicked)
{
	m_sticksPicked = std::to_string(sticksPicked);
	m_infoBar[4].setText(m_sticksPicked);
}
//----------------------------------------------------------------------------------
void InfoBar::updateSticksLeft(int sticksLeft)
{
	m_sticksLeft = std::to_string(sticksLeft);
	m_infoBar[5].setText(m_sticksLeft);
}
//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::printInfoBar(sf::RenderWindow& window)const
{
	window.draw(m_infoBackground);
	window.draw(m_text);

	for (auto index = 0; index < m_infoBar.size(); index++)
	{
		m_infoBar[index].printInfoItem(window);
	}
}

//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::updateScore(int score)
{
	m_score = std::to_string(score);
	m_infoBar[6].setText(m_score);
}

//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::handleClick(const sf::Vector2f& location, bool& levelOver,bool& pressedSave,bool& pressedHint, bool& musicOn)
{
	if (m_infoBar[2].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		//the player pressed on home
		levelOver = true;
		return;
	}
	else if (m_infoBar[1].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		updateMusic(musicOn);
	}
	else if (m_infoBar[0].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		pressedSave = true;
		return;
	}
	else if (m_infoBar[7].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		pressedHint = true;
		return;
	}
}

//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::updateMusic(bool& musicOn)
{
	if (musicOn)
	{
		musicOn = false;
		m_infoBar[1].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_MUTE), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
		HandleResources::instance().stopMusic();
	}
	else
	{
		musicOn = true;
		m_infoBar[1].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
		HandleResources::instance().playMusic();
	}
}

//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::checkMusic(const bool& musicOn)
{
	if (musicOn)
	{
		m_infoBar[1].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
	}
	else
	{
		m_infoBar[1].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_MUTE), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
	}
}