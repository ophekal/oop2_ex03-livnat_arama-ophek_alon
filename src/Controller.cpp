
#include <SFML/Graphics.hpp>
#include <iostream>
#include "HandleResources.h"
#include "Clock.h"
#include "Controller.h"



//------------------------------------------------------------------------------
// This function runs in an infinite loop while the window is open. 
// First, it calls a function that's responsible of generating the game either
// from an existing file or randomly. Then, it starts the game. Once the game is
// over it prints the score.

void Controller::run(sf::RenderWindow& window, bool& load, bool& musicOn)
{
	while (window.isOpen())
	{
		m_board.readTheLevelAndUpdateData(*this,load);

		startGame(window,load, musicOn);

		if (m_levelOver)
		{
			printFinalScore(window);
			return;
		}
	}
}

//------------------------------------------------------------------------------
// This function is responsible of setting the score and time of the game 
// according to what has been read from the file

void Controller::setData(float time, int score, int sticksPicked)
{
	m_totalScore = score;
	m_levelTime = time;
	m_removableSticks = m_board.getRemovableSticks();
	m_sticksLeft = m_board.getNumOfSticks();
	m_sticksPicked = sticksPicked;
}

//------------------------------------------------------------------------------
void Controller::startGame(sf::RenderWindow& window,bool load, bool& musicOn)
{
	sf::Clock clock = m_clock.getClock();

	updateInfoBar(musicOn);

	m_clock.setClock(m_levelTime, m_levelOver);

	while (m_board.getNumOfSticks()!=0)
	{
		print(window);
		if (m_levelOver)
		{
			return;
		}
		windowPollEvent(window, musicOn);
		updateInfoBar(musicOn);
	}

	m_levelOver = true;
}

//----------------------------------------------------------------------------------------
// This function is responsible of handeling the different poll events

void Controller::windowPollEvent(sf::RenderWindow& window, bool& musicOn)
{
	if (auto event = sf::Event{}; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			handleClick(event.mouseButton, window, musicOn);
			break;
		}
	}
}

//----------------------------------------------------------------------------------------
void Controller::print(sf::RenderWindow& window)
{
	window.clear();
	m_infoBar.printInfoBar(window);
	m_board.printBoard(window);
	m_clock.printClock(window, m_levelOver);
	window.display();
}

//----------------------------------------------------------------------------------------
void Controller::handleClick(const sf::Event::MouseButtonEvent& event,
	                         sf::RenderWindow& window, bool& musicOn)
{
	auto location = window.mapPixelToCoords({ event.x,event.y });

	handleClickInfoBar(window,location, musicOn);
	handleClickBoard(window,location);
}

//---------------------------------------------------------------------------------------
void Controller::handleClickBoard(sf::RenderWindow& window,const sf::Vector2f& location)
{
	//checking if we're inside the board
	if (location.y >= BOARD_START_Y && location.y <= WINDOW_HEIGHT &&
		location.x >= BOARD_START_X && location.x <= WINDOW_WIDTH)
	{
		m_board.checkIfPressedOnStick(window, *this,location);
	}
}

//---------------------------------------------------------------------------------------
void Controller::handleClickInfoBar(sf::RenderWindow& window,const sf::Vector2f& location, bool& musicOn)
{
	bool pressedSave = false;
	bool pressedHint = false;

	//checking if we're in the infobar
	if (location.y >= INFO_START_Y && location.y <= INFO_HIG &&
		location.x >= INFO_START_X && location.x <= INFO_WID)
	{
		m_infoBar.handleClick(location, m_levelOver, pressedSave,pressedHint, musicOn);
	}
	if (pressedSave)
	{
		m_board.handlePressedSave(m_totalScore, m_clock.getTimer(), m_sticksPicked);
	}
	else if (pressedHint)
	{
		m_board.handlePressedHint(window,*this);
	}
	
}

//----------------------------------------------------------------------------------------
void Controller::updateInfoBar(bool& musicOn)
{
	m_infoBar.setInfoBar(m_totalScore,m_removableSticks,m_sticksPicked,m_sticksLeft, musicOn);
}

//----------------------------------------------------------------------------------------
void Controller::printFinalScore(sf::RenderWindow& window)
{
	sf::Sprite scorePic(*HandleResources::instance().getBackgroundTexture(B_FINALSCORE));
	sf::Vector2u textureSize = (*HandleResources::instance().getBackgroundTexture(B_FINALSCORE)).getSize();

	//Scale the background sprite to fit the window
	scorePic.setScale((float)(window.getSize().x) / textureSize.x,
		(float)(window.getSize().y) / textureSize.y);

	sf::Text printText;
	printText.setFont(*HandleResources::instance().getFont());

	printText.setString(std::to_string(m_totalScore));
	printText.setCharacterSize(SCORE_TEXT_SIZE);
	printText.setFillColor(sf::Color::Black);

	// Set the position of the text to be centered within the rectangle
	sf::FloatRect textBounds = printText.getLocalBounds();
	float textX = scorePic.getPosition().x + (scorePic.getGlobalBounds().width - textBounds.width) / 2;
	float textY = scorePic.getPosition().y + (scorePic.getGlobalBounds().height - textBounds.height) / 2;
	printText.setPosition(textX, textY);

	window.clear();
	window.draw(scorePic);
	window.draw(printText);
	window.display();
	sf::sleep(sf::seconds(1.5));
}

//----------------------------------------------------------------------------------
void Controller::setScore(int score)
{
	m_totalScore += score;
}

//---------------------------------------------------------------------------------
void Controller::incStickPicked()
{
	m_sticksPicked ++;
}

//---------------------------------------------------------------------------------
// This function updates the number of sticks that can be removed currently
// according to the int value sent

void Controller::setRemovable(int removable)
{
	m_removableSticks = removable;
}

//--------------------------------------------------------------------------------
void Controller::decSticksLeft()
{
	m_sticksLeft--;
}
