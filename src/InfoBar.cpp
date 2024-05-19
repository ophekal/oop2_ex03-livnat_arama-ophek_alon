
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
	m_infoBar.resize(3);
	m_infoBar[0].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_SAVE), SAVE_X, SOUND_Y, SOUND_SIZE);
	m_infoBar[1].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
	m_infoBar[2].updateInfoItem(*HandleResources::instance().getInfoBarTexture(B_HOME), HOME_X, HOME_Y, SOUND_SIZE);
	//m_infoBar[0].updateButton(*HandleResources::instance().getInfoBarTexture(B_INFO), INFO_X, INFO_Y, INFO_SIZE);
	//m_infoBar[1].updateButton(*HandleResources::instance().getInfoBarTexture(B_LEVEL), INFO_X, LEVEL_Y, INFO_SIZE);
	//m_infoBar[2].updateButton(*HandleResources::instance().getInfoBarTexture(B_LIVES), INFO_X, LIVES_Y, INFO_SIZE);
	//m_infoBar[3].updateButton(*HandleResources::instance().getInfoBarTexture(B_KEYS), INFO_X, KEYS_Y, INFO_SIZE);
	//m_infoBar[4].updateButton(*HandleResources::instance().getInfoBarTexture(B_HOME), HOME_X, HOME_Y, SOUND_SIZE);
	//m_infoBar[5].updateButton(*HandleResources::instance().getBackgroundTexture(B_SOUND), I_SOUND_X, I_SOUND_Y, SOUND_SIZE);
	//m_infoBar[6].updateButton(*HandleResources::instance().getInfoBarTexture(B_SCORE), INFO_X, SCORE_Y, INFO_SIZE);
	//m_infoBar[7].updateButton(*HandleResources::instance().getInfoBarTexture(B_RESTART), RESTART_X, RESTART_Y, SOUND_SIZE);

}

////----------------------------------------------------------------------------------------------------------------------------
void InfoBar::setInfoBar(int score, bool& musicOn)
{
	//updateLife(lives);
	updateScore(score);
	//updateKey(key);
	//updateLevel(levelNum);
	checkMusic(musicOn);
}

//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::printInfoBar(sf::RenderWindow& window)const
{
	window.draw(m_infoBackground);
	for (auto index = 0; index < m_infoBar.size(); index++)
	{
		m_infoBar[index].printInfoItem(window);
	}
}

////----------------------------------------------------------------------------------------------------------------------------
//void InfoBar::updateLife(int lives)
//{
//	m_numOfLives = std::to_string(lives);
//	m_infoBar[2].setText(m_numOfLives);
//}
//
////----------------------------------------------------------------------------------------------------------------------------
void InfoBar::updateScore(int score)
{
	/*m_score = std::to_string(score);
	m_infoBar[1].setText(m_score);*/
}

////----------------------------------------------------------------------------------------------------------------------------
//void InfoBar::updateKey(int keys)
//{
//	m_numOfKeys = std::to_string(keys);
//	m_infoBar[3].setText(m_numOfKeys);
//}
//
////----------------------------------------------------------------------------------------------------------------------------
//void InfoBar::updateLevel(int level)
//{
//	m_numOfLevel = std::to_string(level);
//	m_infoBar[1].setText(m_numOfLevel);
//}
//
//----------------------------------------------------------------------------------------------------------------------------
void InfoBar::handleClick(const sf::Vector2f& location, bool& levelOver,bool& pressedSave, bool& musicOn)
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
		//handleSave();
	}
	//else if (m_infoBar[7].getRectangleButton().getGlobalBounds().contains(location))
	//{
	//	levelOver = true;
	//	Mouse* mousePtr = dynamic_cast<Mouse*>(mouse.get());
	//	if (mousePtr != nullptr)
	//	{
	//		mousePtr->setLives(mousePtr->getLives() + 1);	//in order for life not to change when restarting level
	//	}
	//	return;
	//}
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