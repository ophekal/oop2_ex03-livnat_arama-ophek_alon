
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

		//if (m_gameOver)
		//{
			//	printFinalScore(window);
			//return;
		//}

		//printFeedback(*HandleResources::instance().getScreenTexture(S_WIN), window, background, G_WIN);
		//printFinalScore(window);
		//return;
	}
}

//------------------------------------------------------------------------------
//This function is responsible of setting the score and time of the game 
//according to what has been read from the file
void Controller::setData(float time, int score)
{
	m_totalScore = score;
	m_levelTime = time;
}

//------------------------------------------------------------------------------
void Controller::startGame(sf::RenderWindow& window,bool load, bool& musicOn)
{
	sf::Clock clock = m_clock.getClock();

	updateInfoBar(musicOn);

	m_clock.setClock(m_levelTime, m_levelOver);

	while (!m_levelOver || Stick::getCount() == 0)
	{
		print(window);
		windowPollEvent(window, musicOn);

		//const auto deltaTime = clock.restart();

		updateInfoBar(musicOn);
	}

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
	m_board.printBoard(window);
	m_infoBar.printInfoBar(window);
	m_clock.printClock(window, m_levelOver);
	window.display();
}

////----------------------------------------------------------------------------------------
//bool Controller::checkGameStatus(int numOfCheese, int numOfCats, sf::RenderWindow& window,
//	const sf::Sprite& background, bool& musicOn)
//{
//	if (m_mouseDead)
//	{
//		Mouse* mousePtr = dynamic_cast<Mouse*>(m_mouse.get());
//		if (mousePtr != nullptr)
//		{
//			if ((mousePtr->getLives()) == 0)
//			{
//				handleExit(window, background);
//				return true;
//			}
//		}
//
//		//handle dead mouse while life isn't zero
//		handleDeadMouse(window, background);
//		return false;
//	}
//	return checkLevelStatus(numOfCheese, numOfCats, window, background, musicOn);
//}
//
////----------------------------------------------------------------------------------------
//bool Controller::checkLevelStatus(int numOfCheese, int numOfCats, sf::RenderWindow& window,
//	const sf::Sprite& background, bool& musicOn)
//{
//	if (numOfCheese == 0) //to the next level
//	{
//		print(window, background);
//		printFeedback(*HandleResources::instance().getScreenTexture(S_GOODJOB), window, background, G_WIN);
//		Mouse* mousePtr = dynamic_cast<Mouse*>(m_mouse.get());
//		if (mousePtr != nullptr)
//		{
//			m_totalScore = mousePtr->getScore();
//			m_totalScore += 25;
//			m_totalScore += (5 * numOfCats);
//		}
//		m_board.clear();
//		m_cats.clear();
//		return true;
//	}
//
//	if (m_levelOver)
//	{
//		// start the level again
//		handleLevelOver(window, background, musicOn);
//		return false;
//	}
//
//	return false;
//}
//
//
////----------------------------------------------------------------------------------------
//void Controller::handleLevelOver(sf::RenderWindow& window, const sf::Sprite& background, bool& musicOn)
//{
//	printFeedback(*HandleResources::instance().getScreenTexture(S_TRYAGAIN), window, background, G_LOST);
//
//	Mouse* mousePtr = dynamic_cast<Mouse*>(m_mouse.get());
//	int prevLives = 0;
//
//	if (mousePtr != nullptr)
//	{
//		prevLives = mousePtr->getLives() - 1;
//		if (prevLives == 0)
//		{
//			handleExit(window, background);
//			return;
//		}
//	}
//
//	// load the same level again with all the objects
//	m_board.reset();
//	m_cats.clear();
//	m_board.updateBoard(m_cats, m_mouse, m_levelTime);
//
//	Mouse* newMousePtr = dynamic_cast<Mouse*>(m_mouse.get());
//	if (newMousePtr != nullptr)
//	{
//		newMousePtr->setLives(prevLives);
//		newMousePtr->setScore(m_prevLevelsScore);
//	}
//	updateInfoBar(musicOn);
//	m_clock.setClock(m_levelTime, m_levelOver);
//}
//
////----------------------------------------------------------------------------------------
//void Controller::handleExit(sf::RenderWindow& window, const sf::Sprite& background)
//{
//	m_gameOver = true;
//	printFeedback(*HandleResources::instance().getScreenTexture(S_GAMEOVER), window, background, G_LOST);
//}
//
//----------------------------------------------------------------------------------------
void Controller::handleClick(const sf::Event::MouseButtonEvent& event,
	sf::RenderWindow& window, bool& musicOn)
{
	auto location = window.mapPixelToCoords({ event.x,event.y });

	handleClickInfoBar(location);
	handleClickBoard(location);
}
//---------------------------------------------------------------------------------------
void Controller::handleClickBoard(const sf::Vector2f& location)
{
	//checking if we're in the tool bar
	if (location.y >= 0 && location.y <= 950 &&	                  
		location.x >= 450 && location.x <= 1500)						
	{
		
	}
}
//---------------------------------------------------------------------------------------
void Controller::handleClickInfoBar(const sf::Vector2f& location)
{
	//checking if we're in the tool bar
	if (location.y >= 0 && location.y <= 950  &&	//the range of Y in the toolbar
		location.x >= 0 && location.x <= 450)						//the range of X in the toolbar
	{
		//m_infoBar.handleClick(location, m_gameOver, m_levelOver, m_mouse, musicOn);
	}
	
}
//----------------------------------------------------------------------------------------
void Controller::updateInfoBar(bool& musicOn)
{
	
	//int keys = 0;
	//int lives = 0;

	//if (mousePtr != nullptr)
	//{
	//	keys = mousePtr->getKeys();
	//	m_totalScore = mousePtr->getScore();
	//	lives = mousePtr->getLives();
	//}
	//m_infoBar.setInfoBar(m_levelNum, m_totalScore, keys, lives, musicOn);
}

////----------------------------------------------------------------------------------------
//void Controller::updateScore()
//{
//	
//}
//
////----------------------------------------------------------------------------------------
//void Controller::printFeedback(const sf::Texture& feedback,
//	sf::RenderWindow& window,
//	const sf::Sprite& background, GameSound sound)const
//{
//	sf::sleep(sf::seconds(1));
//	sf::Sprite sprite(feedback);
//	sprite.setPosition(window.getSize().x / 2.0f - sprite.getLocalBounds().width / 2.0f,
//		window.getSize().y / 2.0f - sprite.getLocalBounds().height / 2.0f);
//
//	window.clear();
//	window.draw(background);
//	HandleResources::instance().playSound(sound);
//	window.draw(sprite);
//	window.display();
//	sf::sleep(sf::seconds(1));
//}
//
////----------------------------------------------------------------------------------------
//void Controller::printFinalScore(sf::RenderWindow& window)
//{
//	sf::Sprite scorePic(*HandleResources::instance().getScreenTexture(S_FINALSCORE));
//	sf::Vector2u textureSize = (*HandleResources::instance().getScreenTexture(S_FINALSCORE)).getSize();
//
//	//Scale the background sprite to fit the window
//	scorePic.setScale((float)(window.getSize().x) / textureSize.x,
//		(float)(window.getSize().y) / textureSize.y);
//
//	sf::Text printText;
//	printText.setFont(*HandleResources::instance().getFont());
//
//	printText.setString(std::to_string(m_totalScore));
//	printText.setCharacterSize(SCORE_TEXT_SIZE);
//	printText.setFillColor(sf::Color::Black);
//
//	// Set the position of the text to be centered within the rectangle
//	sf::FloatRect textBounds = printText.getLocalBounds();
//	float textX = scorePic.getPosition().x + (scorePic.getGlobalBounds().width - textBounds.width) / 2;
//	float textY = scorePic.getPosition().y + (scorePic.getGlobalBounds().height - textBounds.height) / 4;
//	printText.setPosition(textX, textY);
//
//	window.clear();
//	window.draw(scorePic);
//	window.draw(printText);
//	window.display();
//	sf::sleep(sf::seconds(2));
//}
