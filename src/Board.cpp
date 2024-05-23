
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <random>
#include "Macros.h"
#include <vector>
#include "InvalidFileException.h"
#include "WrongInputException.h"
#include "Board.h"
#include "Stick.h"
#include "Controller.h"

//-------------------------------------------------------------------------------------
Board::Board()
	: m_board(sf::Vector2f(BOARD_WID, BOARD_HIG))
{
	m_board.setPosition({ BOARD_START_X ,BOARD_START_Y });
	m_board.setTexture(HandleResources::instance().getBackgroundTexture(B_BOARD));
}

//-------------------------------------------------------------------------------------
// This function checks if the user wants to upload a saved game.
// If the user pressed on "load game" it calls on a function that reads the level and
// starts the game. If not it calls the function that generates a random game

void Board::readTheLevelAndUpdateData(Controller& controller, bool& load)
{
	if (load)
	{
		loadAndRunFromExisting(controller, load);
	}
	else
	{
		generateGame(controller);
	}
}

//-------------------------------------------------------------------------------------
void Board::loadAndRunFromExisting(Controller& controller, bool& load)
{
	bool firstLine = true;
	float time = 0;						  //default value
	int score = 0, sticksPicked = 0;      //defalut value

	auto file = std::ifstream("level.txt");

	if (!file.is_open())
	{
		load = false;
		throw InvalidFileException();
	}

	for (auto line = std::string(); std::getline(file, line); )
	{
		std::istringstream iss(line);

		if (firstLine)
		{
			if (!(iss >> time >> score >> sticksPicked))
			{
				throw  WrongInputException();
			}
			firstLine = false;
		}
		else
		{
			float angle, x, y,len;
			int colour;
			if (!(iss >> colour >> angle >> len >> x >> y))
			{
				throw  WrongInputException();
			}
			Stick stick(HandleResources::instance().getObjectTexture(StickType(colour)), Colour(colour), angle, { x,y }, len);
			addStickToList(stick);
		}
	}

	// calling the function that updates the removabe multimap
	updateRemoveable();
	updateControllerData(controller, time, score, sticksPicked);
}

//-------------------------------------------------------------------------------------
// This function is responsoble of creating a random level

void Board::generateGame(Controller& controller)
{
	// Generate a random number of sticks
	int numSticks = randomFloat(15, 45);

	// Create the sticks and insert them into the list
	for (int i = 0; i < numSticks; ++i) 
	{
		createRandomStick();		
	}

	// after creating the list update the multimap that holds the removeable sticks
	updateRemoveable();	

	float time = m_sticks.size() >= 30 ? LONG_LEVEL : SHORT_LEVEL;
	updateControllerData(controller, time, 0, 0);
}

//-------------------------------------------------------------------------------------
void Board::createRandomStick()
{
	float x = 0, y = 0, len = 0, angle = 0;
	int colour = 0;

	while (1)
	{
		// Generate random values within the board area
		x = randomFloat(BOARD_START_X+15, BOARD_START_X + BOARD_WID),
		y = randomFloat(BOARD_START_Y,BOARD_HIG),
		len = randomFloat(15, BOARD_WID / 10.0f),
		angle = randomFloat(1, 179);

		// Generate random color
		colour = rand() % 5;

		Stick stick(HandleResources::instance().getObjectTexture(StickType(colour)), Colour(colour), angle, {x,y}, len);
		sf::Vector2f endPoint = stick.getEndPoint();
		if (endPoint.y >= BOARD_START_Y+10 && endPoint.y <= BOARD_HIG-10 &&
			endPoint.x >= BOARD_START_X + 15 && endPoint.x <= WINDOW_WIDTH-10)
		{
			addStickToList(stick);
			return;
		}
	}
	
}
//-------------------------------------------------------------------------------------
// Function that generates a random float in a given range

float Board::randomFloat(float min, float max)const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

//-------------------------------------------------------------------------------------
// This function is responsible of updating the data according to what was in the
// saved file

void Board::updateControllerData(Controller& controller, float time, int score, int sticksPicked) const
{
	controller.setData(time, score, sticksPicked);
}

//------------------------------------------------------------------------------------
int Board::getRemovableSticks()const
{
	return m_removeable.size();
}

//-------------------------------------------------------------------------------------
void Board::addStickToList(Stick& stick)
{	
	m_sticks.push_back(stick);
	
	//go over all the prev sticks and check if this stick block them
	for (auto it = m_sticks.begin(); it != std::prev(m_sticks.end()); it++)
	{
		if (stick.checkAndUpdateIntersection(*it))
		{
			it->updateSticksBlocking(&m_sticks.back());
		}
	}
}
//-----------------------------------------------------------------------------
// This function goes over the sticks and ccheck per stick if it's free, if so
// it adds it to the removeable multimap
 
void Board::updateRemoveable()
{
	//go over the list and check for the removeable sticks
	for (auto it = m_sticks.begin(); it != m_sticks.end(); it++)
	{
		if ( it-> isFree())
		{
			m_removeable.insert(std::make_pair(it->getStickScore(),&(*it)));
		}
	}
}

//-----------------------------------------------------------------------------
// This function is responsible of updating all the relevant data structures
// once a stick is being removed

void Board::updateDataAndDeleteStick( std::list<Stick>::reverse_iterator& needToRemoveIt)
{
	needToRemoveIt->handleStickRemove(m_removeable);
	deleteStick(needToRemoveIt);
}

//-----------------------------------------------------------------------------
// This function is responsible of removing the stick from the removeable
// multimap and sticks list

void Board::deleteStick(std::list<Stick>::reverse_iterator& needToRemoveIt)
{
	Stick* objectToDelete = &(*needToRemoveIt);

	// remove the element from the list using erase after coverting to iterator
	m_sticks.erase(std::next(needToRemoveIt).base());

	// remove all pointers to the object from the multimap
	for (auto it = m_removeable.begin(); it != m_removeable.end(); ++it) 
	{
		if (it->second == objectToDelete) 
		{
			it = m_removeable.erase(it);
			break;
		}
	}
}

//-------------------------------------------------------------------------------------
void Board::printBoard(sf::RenderWindow& window)
{
	window.draw(m_board);

	//go over the sticks list and draw the sticks
	for (auto it = m_sticks.begin(); it != m_sticks.end(); it++)
	{
		it -> draw(window);
	}
}
//-------------------------------------------------------------------------------------
void Board::handlePressedSave(int score,float levelTime, int sticksPicked) const
{
	std::ofstream boardFile;
	if (std::filesystem::exists("level.txt"))
	{
		std::remove("level.txt");
	}

	boardFile.open("level.txt");
	if (boardFile.is_open())
	{
		saveBoardAndCopyToText(boardFile, score, levelTime, sticksPicked);
	}
}

//---------------------------------------------------------------------------------------
void Board::saveBoardAndCopyToText(std::ofstream& boardFile, int score, float levelTime, int sticksPicked)const
{
	std::string info;

	info = std::to_string(levelTime) + " " + std::to_string(score) + " " + std::to_string(sticksPicked)+ "\n";
	boardFile << info;

	for (auto it = m_sticks.begin(); it != m_sticks.end(); it++)
	{
		info = it->getStickInfo();
		boardFile << info;
	}

}
//---------------------------------------------------------------------------------------
int Board::getNumOfSticks()const
{
	return m_sticks.size();
}

//---------------------------------------------------------------------------------------
// This function loops through the removeable multimap and higlights them one by one 
// according to there value
 
void Board::handlePressedHint(sf::RenderWindow& window, Controller& controller)
{
	for (auto it = m_removeable.rbegin(); it != m_removeable.rend(); it++)
	{
		it ->second ->highlightStick();
		controller.print(window);
		sf::sleep(sf::seconds(1));
		it->second->stopHighlightStick();
		controller.print(window);
		sf::sleep(sf::seconds(0.3));
	}
}

//---------------------------------------------------------------------------------------
// This function goes over the stick list and check if we pressed one of them

void Board::checkIfPressedOnStick(sf::RenderWindow& window, Controller& controller, const sf::Vector2f& location)
{
	for (auto it = m_sticks.rbegin(); it != m_sticks.rend(); it++)
	{
		if (it->pressed(location) && it->isFree() )
		{
			HandleResources::instance().playSound(G_FREE);
			controller.setScore(it->getStickScore());
			updateDataAndDeleteStick(it);
			controller.incStickPicked();
			controller.setRemovable(m_removeable.size());
			controller.decSticksLeft();
			return;
		}
		else if (it->pressed(location) && !it->isFree())
		{
			HandleResources::instance().playSound(G_BLOCKED);
			highlightBlockingSticks(window, controller, *it);
			return;
		}
	}
}

//-------------------------------------------------------------------------------

void Board::highlightBlockingSticks(sf::RenderWindow& window,Controller& controller, Stick& stick)
{
	stick.highlightBlockingSticks();
	controller.print(window);
	sf::sleep(sf::seconds(0.5));
	stick.stopHighlightBlockingSticks();
}

