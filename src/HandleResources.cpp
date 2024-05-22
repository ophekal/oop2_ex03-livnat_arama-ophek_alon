
#include "HandleResources.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Macros.h"


//------------------------------------------------------------------------
HandleResources::HandleResources()
{
	//update all the resources of the game
	updateObjectVector();
	updateBackgroundVector();
	updateInfoBarVector();
	updateBufferSounds();
	updateGameSounds();
	m_font.loadFromFile("font.ttf");
	m_gameMusic.openFromFile("gameMusic.wav");
}

//------------------------------------------------------------------------
HandleResources& HandleResources::instance()
{
	static HandleResources inst;
	return inst;
}

//------------------------------------------------------------------------
void HandleResources::updateObjectVector()
{
	m_objectsTextures.resize(5);
	m_objectsTextures[S_BLACK_STICK].loadFromFile("blackStick.png");
	m_objectsTextures[S_RED_STICK].loadFromFile("redStick.png");
	m_objectsTextures[S_BLUE_STICK].loadFromFile("blueStick.png");
	m_objectsTextures[S_GREEN_STICK].loadFromFile("greenStick.png");
	m_objectsTextures[S_YELLOW_STICK].loadFromFile("yellowStick.png");
}

//-------------------------------------------------------------------------
void HandleResources::updateBackgroundVector()
{
	m_backgroundsTextures.resize(11);
	m_backgroundsTextures[B_MENU].loadFromFile("menu.jpg");
	m_backgroundsTextures[B_BOARD].loadFromFile("boardBackground.png");
	m_backgroundsTextures[B_EXIT].loadFromFile("exitButton.png");
	m_backgroundsTextures[B_START].loadFromFile("startGame.png");
	m_backgroundsTextures[B_RULES].loadFromFile("gameRules.png");
	m_backgroundsTextures[B_LOAD].loadFromFile("loadGame.png");
	m_backgroundsTextures[B_GAMERULES].loadFromFile("gameRulesWindow.png");
	m_backgroundsTextures[B_SOUND].loadFromFile("music.png");
	m_backgroundsTextures[B_MUTE].loadFromFile("mute.png");
	m_backgroundsTextures[B_INFOBAR].loadFromFile("infoBar.png");
	m_backgroundsTextures[B_FINALSCORE].loadFromFile("scoreFeedback.jpg");
}

//-------------------------------------------------------------------------
void HandleResources::updateInfoBarVector()
{
	m_infoBarTextures.resize(8);
	m_infoBarTextures[B_TIME].loadFromFile("time.png");
	m_infoBarTextures[B_SAVE].loadFromFile("saveButton.png");
	m_infoBarTextures[B_HOME].loadFromFile("home.png");
	m_infoBarTextures[B_FREE].loadFromFile("freeSticks.png");
	m_infoBarTextures[B_PICKEDUP].loadFromFile("pickedUp.png");
	m_infoBarTextures[B_LEFT].loadFromFile("sticksLeft.png");
	m_infoBarTextures[B_SCORE].loadFromFile("score.png");		
	m_infoBarTextures[B_HINT].loadFromFile("hintButton.png");		
}

//-------------------------------------------------------------------------
void HandleResources::updateBufferSounds()
{
	m_bufferSounds.resize(2);
	m_bufferSounds[G_FREE].loadFromFile("pickedUp.wav");
	m_bufferSounds[G_BLOCKED].loadFromFile("blockedStick.wav");
}

//-------------------------------------------------------------------------
void HandleResources::updateGameSounds()
{
	m_gameSound.resize(2);
	m_gameSound[G_FREE].setBuffer(m_bufferSounds[G_FREE]);
	m_gameSound[G_BLOCKED].setBuffer(m_bufferSounds[G_BLOCKED]);
}

//--------------------------------------------------------------------------
const sf::Texture* HandleResources::getInfoBarTexture(Bar icon)
{
	return &(m_infoBarTextures[icon]);
}


//-------------------------------------------------------------------------
const sf::Texture* HandleResources::getObjectTexture(StickType icon)
{
	return &(m_objectsTextures[icon]);
}

//-------------------------------------------------------------------------
const sf::Texture* HandleResources::getBackgroundTexture(Background icon)
{
	return &(m_backgroundsTextures[icon]);
}

//-------------------------------------------------------------------------
const sf::Font* HandleResources::getFont()
{
	return &m_font;
}

//-------------------------------------------------------------------------
void HandleResources::playSound(GameSound sound)
{
	m_gameSound[sound].setVolume(100);
	m_gameSound[sound].play();
}

//-------------------------------------------------------------------------
void HandleResources::playMusic()
{
	m_gameMusic.setLoop(true);
	m_gameMusic.play();
}

//--------------------------------------------------------------------------
void HandleResources::stopMusic()
{
	m_gameMusic.pause();
}