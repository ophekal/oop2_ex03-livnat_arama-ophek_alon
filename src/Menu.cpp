
#include "Menu.h"
#include <vector>
#include <string.h>
#include <fstream>
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "HandleResources.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

//--------------------------------------------------------------------------------------------
Menu::Menu()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), " ")
{
	updateButton();
}

//--------------------------------------------------------------------------------------------
void Menu::run()
{
	HandleResources::instance().playMusic();
	sf::Sprite background;
	const sf::Texture* backgroundTexture = HandleResources::instance().getBackgroundTexture(B_MENU);
	background.setTexture(*backgroundTexture);
	sf::Vector2u textureSize = (*backgroundTexture).getSize();

	// Scale the background sprite to fit the window
	background.setScale((float)(m_window.getSize().x) / textureSize.x,
		(float)(m_window.getSize().y) / textureSize.y);

	while (m_window.isOpen())
	{
		print(background);
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				handleClick(event.mouseButton);
				break;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
void Menu::updateButton()
{
	m_buttons[M_START].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_START), START_X, START_Y, BUTTON_SIZE);
	m_buttons[M_EXIT].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_EXIT), EXIT_X, EXIT_Y, BUTTON_SIZE);
	m_buttons[M_LOAD].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_LOAD), LOAD_X, LOAD_Y, BUTTON_SIZE);
	m_buttons[M_SOUND].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), SOUND_X, SOUND_Y, SOUND_SIZE);
	m_buttons[M_RULES].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_RULES), RULES_X,	RULES_Y, BUTTON_SIZE);
}

//--------------------------------------------------------------------------------------------
void Menu::print(const sf::Sprite& background)
{
	m_window.clear();
	m_window.draw(background);
	printButtons();
	m_window.display();
}

//--------------------------------------------------------------------------------------------
void Menu::printButtons()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

	//increase the buttons when mouse ontop
	for (int i = 0; i < 5; i++)
	{
		sf::RectangleShape& button = m_buttons[i].getRectangleInfoItem();
		sf::FloatRect bounds = button.getGlobalBounds();

		if (bounds.contains(mousePosF))
		{
			button.setScale(1.05f, 1.05f);
		}
		else
		{
			button.setScale(1.0f, 1.0f);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		m_buttons[i].printInfoItem(m_window);
	}
}

//--------------------------------------------------------------------------------------------
void Menu::handleClick(sf::Event::MouseButtonEvent& event)
{
	auto location = m_window.mapPixelToCoords({ event.x,event.y });

	if (m_buttons[M_START].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		startGame();	//calls on controller and starts the game
	}
	else if (m_buttons[M_EXIT].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		m_window.close();
		return;
	}
	else if (m_buttons[M_SOUND].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		handleMusic();
	}
	else if (m_buttons[M_RULES].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		pressedGameRules();	//creates a window that explains the game
	}
	else if (m_buttons[M_LOAD].getRectangleInfoItem().getGlobalBounds().contains(location))
	{
		handleLoad();
	}
}

//--------------------------------------------------------------------------------------------
void Menu::handleLoad()
{
	if (std::filesystem::exists("level.txt"))
	{
		m_load = true;
	}
	startGame();
}
//--------------------------------------------------------------------------------------------
void Menu::pressedGameRules()
{
	sf::Sprite rules;
	const sf::Texture* backgroundTexture = HandleResources::instance().getBackgroundTexture(B_GAMERULES);
	rules.setTexture(*backgroundTexture);
	sf::Vector2u textureSize = (*backgroundTexture).getSize();

	sf::RenderWindow gameRulesWindow(sf::VideoMode(GAMERULES, GAMERULES), "Game Rules");

	// Scale the background sprite to fit the window
	rules.setScale((float)(gameRulesWindow.getSize().x) / textureSize.x,
		(float)(gameRulesWindow.getSize().y) / textureSize.y);

	while (gameRulesWindow.isOpen())
	{
		gameRulesWindow.clear();
		gameRulesWindow.draw(rules);
		gameRulesWindow.display();

		if (auto event = sf::Event{}; gameRulesWindow.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				gameRulesWindow.close();
				break;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
void Menu::startGame()
{
	Controller controller;
	controller.run(m_window,m_load, m_musicOn);
	checkMusic();
}

//--------------------------------------------------------------------------------------------
void Menu::handleMusic()
{
	if (m_musicOn)
	{
		m_musicOn = false;
		m_buttons[M_SOUND].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_MUTE), SOUND_X, SOUND_Y, SOUND_SIZE);
		HandleResources::instance().stopMusic();
	}
	else
	{
		m_musicOn = true;
		m_buttons[M_SOUND].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), SOUND_X, SOUND_Y, SOUND_SIZE);
		HandleResources::instance().playMusic();
	}
}

//--------------------------------------------------------------------------------------------
void Menu::checkMusic()
{
	if (m_musicOn)
	{
		m_buttons[M_SOUND].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_SOUND), SOUND_X, SOUND_Y, SOUND_SIZE);
	}
	else
	{
		m_buttons[M_SOUND].updateInfoItem(*HandleResources::instance().getBackgroundTexture(B_MUTE), SOUND_X, SOUND_Y, SOUND_SIZE);
	}
}
