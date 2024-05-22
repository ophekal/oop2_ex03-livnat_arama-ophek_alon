
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "HandleResources.h"
#include "Clock.h"


//------------------------------------------------------------------------------
//This function is responsible of opening the ifstream in order to read the
//levels. It calls on functions that handle the game
//This function handles with an open window. It reads the level from the file
//and with the help of other functions it copies it to the game board, and
//starts the game.

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
//This function is responsible of setting the score and time of the game 
//according to what has been read from the file
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
//This function is responsible of handeling the different poll events

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
	if (location.y >= 0 && location.y <= 950 &&	                  
		location.x >= 450 && location.x <= 1500)						
	{
		m_board.checkIfPressedOnStick(window, *this,location);
	}
}
//---------------------------------------------------------------------------------------
void Controller::handleClickInfoBar(sf::RenderWindow& window,const sf::Vector2f& location, bool& musicOn)
{
	bool pressedSave = false;
	bool pressedHint = false;

	//checking if we're in the tool bar
	if (location.y >= 0 && location.y <= 950  &&	
		location.x >= 0 && location.x <= 450)						
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
void Controller::setRemovable(int removable)
{
	m_removableSticks = removable;
}
//--------------------------------------------------------------------------------
void Controller::decSticksLeft()
{
	m_sticksLeft--;
}
