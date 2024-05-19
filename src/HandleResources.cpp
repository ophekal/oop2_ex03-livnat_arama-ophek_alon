
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
	//updateScreenVector();
	//updateBufferSounds();
	//updateGameSounds();
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
	m_backgroundsTextures.resize(10);
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
}

//-------------------------------------------------------------------------
void HandleResources::updateInfoBarVector()
{
	m_infoBarTextures.resize(3);
	//m_infoBarTextures[B_INFO].loadFromFile("information.png");
	//m_infoBarTextures[B_LEVEL].loadFromFile("level.png");
	//m_infoBarTextures[B_LIVES].loadFromFile("lives.png");
	//m_infoBarTextures[B_KEYS].loadFromFile("keys.png");
	m_infoBarTextures[B_TIME].loadFromFile("time.png");

	//m_infoBarTextures[B_SCORE].loadFromFile("score.png");
	//m_infoBarTextures[B_RESTART].loadFromFile("restart.png");
	m_infoBarTextures[B_SAVE].loadFromFile("save.jpg");
	m_infoBarTextures[B_HOME].loadFromFile("home.png");
}

//-------------------------------------------------------------------------
//void HandleResources::updateScreenVector()
//{
//	m_screenTextures.resize(5);
//	m_screenTextures[S_WIN].loadFromFile("youWin.png");
//	m_screenTextures[S_GAMEOVER].loadFromFile("gameOver.png");
//	m_screenTextures[S_TRYAGAIN].loadFromFile("tryAgain.png");
//	m_screenTextures[S_GOODJOB].loadFromFile("goodJob.png");
//	m_screenTextures[S_FINALSCORE].loadFromFile("finalScore.png");
//}

////-------------------------------------------------------------------------
//void HandleResources::updateBufferSounds()
//{
//	m_bufferSounds.resize(6);
//	m_bufferSounds[G_CHEESE].loadFromFile("yummy.wav");
//	m_bufferSounds[G_GIFT].loadFromFile("gift.wav");
//	m_bufferSounds[G_MOUSE].loadFromFile("mouseEaten.wav");
//	m_bufferSounds[G_WIN].loadFromFile("goodJobYouWin.wav");
//	m_bufferSounds[G_LOST].loadFromFile("tryAgainGameOver.wav");
//	m_bufferSounds[G_KEY].loadFromFile("keys.wav");
//}

////-------------------------------------------------------------------------
//void HandleResources::updateGameSounds()
//{
//	m_gameSound.resize(6);
//	m_gameSound[G_CHEESE].setBuffer(m_bufferSounds[G_CHEESE]);
//	m_gameSound[G_GIFT].setBuffer(m_bufferSounds[G_GIFT]);
//	m_gameSound[G_MOUSE].setBuffer(m_bufferSounds[G_MOUSE]);
//	m_gameSound[G_WIN].setBuffer(m_bufferSounds[G_WIN]);
//	m_gameSound[G_LOST].setBuffer(m_bufferSounds[G_LOST]);
//	m_gameSound[G_KEY].setBuffer(m_bufferSounds[G_KEY]);
//}

//--------------------------------------------------------------------------
const sf::Texture* HandleResources::getInfoBarTexture(Bar icon)
{
	return &(m_infoBarTextures[icon]);
}

////--------------------------------------------------------------------------
//const sf::Texture* HandleResources::getScreenTexture(Screen icon)
//{
//	return &(m_screenTextures[icon]);
//}

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

////-------------------------------------------------------------------------
//void HandleResources::playSound(GameSound sound)
//{
//	m_gameSound[sound].setVolume(50);
//	m_gameSound[sound].play();
//}

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