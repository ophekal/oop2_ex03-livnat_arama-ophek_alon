#pragma once
#include <SFML/Graphics.hpp>
#include "InfoItem.h"

class InfoItem;

class Menu
{
public:
	Menu();
	void run();

private:
	void updateButton();
	void print(const sf::Sprite& background);
	void printButtons();
	void handleClick(sf::Event::MouseButtonEvent& event);
	void startGame();
	void handleMusic();
	void checkMusic();
	void pressedGameRules();
	void handleLoad();

	sf::RenderWindow m_window;
	InfoItem m_buttons[5];
	bool m_musicOn = true;
	bool m_load = false;
};

