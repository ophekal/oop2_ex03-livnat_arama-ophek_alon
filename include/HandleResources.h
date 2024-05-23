#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string.h>
#include <vector>
#include "Macros.h"

class HandleResources
{
public:
	static HandleResources& instance();

	const sf::Texture* getObjectTexture(StickType icon);
	const sf::Texture* getBackgroundTexture(Background icon);
	const sf::Texture* getInfoBarTexture(Bar icon);
	const sf::Font* getFont();
	void playSound(GameSound sound);
	void playMusic();
	void stopMusic();

private:
	HandleResources();  
	void updateObjectVector();
	void updateBackgroundVector();
	void updateInfoBarVector();
	void updateBufferSounds();
	void updateGameSounds();

	std::vector<sf::Texture> m_objectsTextures;
	std::vector<sf::Texture> m_backgroundsTextures;	//menu, infobar, window
	std::vector<sf::Texture> m_infoBarTextures;		//menu, infobar, window

	sf::Font m_font;
	sf::Music m_gameMusic;
	std::vector <sf::SoundBuffer> m_bufferSounds;
	std::vector <sf::Sound> m_gameSound;

};