
#include "Board.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <random>
#include "Macros.h"
#include <filesystem>
#include "Stick.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Controller.h"

//-------------------------------------------------------------------------------------
Board::Board()
	: m_board(sf::Vector2f(BOARD_WID, BOARD_HIG))
{
	m_board.setPosition({ BOARD_START_X ,BOARD_START_Y });
	m_board.setTexture(HandleResources::instance().getBackgroundTexture(B_BOARD));
	m_board.setOutlineThickness(5.f);
	m_board.setOutlineColor(sf::Color::Black);
}

//-------------------------------------------------------------------------------------
//This function reads the level and inserts it into list and update all the data

void Board::readTheLevelAndUpdateData(Controller& controller, bool load)
{
	if (load)
	{
		loadAndRunFromExisting(controller);
	}
	else
	{
		generateGame(controller);
	}
}

//-------------------------------------------------------------------------------------
void Board::loadAndRunFromExisting(Controller& controller) 
{
	bool firstLine = true;

	auto file = std::ifstream("level.txt");
	try
	{
		if (!file.is_open())
		{
			//throw 
		}

		for (auto line = std::string(); std::getline(file, line); )
		{
			try
			{
				std::istringstream iss(line);

				if (firstLine)
				{
					float time;
					int score;
					if (!(iss >> time >> score))
					{
						//throw  wrong input
					}
					updateControllerData(controller, time, score);
					firstLine = false;
				}
				else
				{
					float angle, x, y,len;
					int colour;
					if (!(iss >> colour >> angle >> len >> x >> y))
					{
						//throw  worng input, if range isn't good, x-y arent goot etc
					}
					addStickToList(StickType(colour), angle, len, x, y);
				}
			}
			catch (std::exception& e)
			{

			}
		}
		updateRemoveable();
	}
	catch (std::exception& e)
	{

	}
}

//-------------------------------------------------------------------------------------
//This function is responsoble of creating the level randomly
void Board::generateGame(Controller& controller)
{
	// Calculate the total area of the board of docks
	float boardArea = (BOARD_WID * BOARD_HIG )/ 10000.0f;

	// Generate a random number of sticks proportional to the size of the board
	int numSticks = randomFloat(25, 50); // randomFloat(0.1f, 0.5f)* boardArea; // Adjust the range according to your preference

	// Create the sticks and insert them into the list
	for (int i = 0; i < numSticks; ++i) 
	{
		createRandomStick();		
	}

	//after create the list check for the removeable sticks
	updateRemoveable();	

	float time = m_sticks.size() >= 35 ? LONG_LEVEL : SHORT_LEVEL;

	updateControllerData(controller, time, 0);
}
//-------------------------------------------------------------------------------------
void Board::createRandomStick()
{
	// Generate random values within the board area
	float x = randomFloat(BOARD_START_X+100 ,BOARD_START_X + BOARD_WID-100),
		  y = randomFloat(BOARD_START_Y , BOARD_START_Y + BOARD_HIG-100),
	      len = randomFloat(19, BOARD_WID / 10.0f),
		  angle = randomFloat(1, 179);


	// Generate random color
	int colour = rand() % 5; 
	addStickToList(StickType(colour), angle, len, x, y);
}
//-------------------------------------------------------------------------------------
// Function to generate a random float in a given range
float Board::randomFloat(float min, float max)const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

//-------------------------------------------------------------------------------------
//This function is responsible of updating the data according to what was saved in the
//existing file
void Board::updateControllerData(Controller& controller, float time, int score) const
{
	controller.setData(time, score);
}
//------------------------------------------------------------------------------------
int Board::getRemovableSticks()const
{
	return m_removeable.size();
}
//-------------------------------------------------------------------------------------
//This function is responsible of adding the stick to the list of sticks
void Board::addStickToList(StickType colour, float angle, float len, float x, float y)
{
	sf::Vector2f point(x,y);
	Stick stick(HandleResources::instance().getObjectTexture(colour), Colour(colour), angle, point, len);
	
	m_sticks.push_back(stick);
	
	//go over all the prev sticks and check if this stick block them
	for (auto it = m_sticks.begin(); it != std::prev(m_sticks.end()); it++)
	{
		if (stick.checkAndUpdateIntersection(*it))
		{
			it->updateSticksBlocking(&stick);
		}
	}
	
}
//-----------------------------------------------------------------------------
void Board::updateRemoveable()
{
	//go over the list and check for the removeable sticks
	for (auto it = m_sticks.begin(); it != m_sticks.end(); it++)
	{
		if (it->getBlockThisStick() == 0 && !(it->getInRemoveable()))
		{
			m_removeable.insert(std::make_pair(it->getStickScore(),&(*it)));
			it->setInRemoveable(true);
		}
	}
}
//
////-----------------------------------------------------------------------------
////after the function delete the stick from the list
//void Board::updateSticksList(auto needToRemoveIt)
//{
//	// change the sticks that this stick blocked
//	*needToRemoveIt.handleStickRemove();
//
//	// update the multimap - delete the pointer to the stick 
//	deleteStick(needToRemoveIt);
//
//	// update the multimap
//	//need to check if the value allready in or this doesnt matter?
//	updateRemoveable();
//
//}
////-----------------------------------------------------------------------------
//
//void Board::deleteStick(auto needToRemoveIt)
//{
//
//	// Iterate through the list and remove the object you want to delete
//	Stick* objectToDelete = m_sticks.remove(needToRemove);
//
//	// Now, remove the pointers to the object from the multimap
//	for (auto it = objectMap.begin(); it != objectMap.end(); ) {
//		if (it->second == objectToDelete) {
//			it = objectMap.erase(it);
//		}
//		else {
//			++it;
//		}
//	}
//
//	// Finally, delete the object itself
//	delete objectToDelete;
//
//}
//
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
void Board::handlePressedSave(int score, float levelTime)const
{
	std::ofstream boardFile;
	if (std::filesystem::exists("level.txt"))
	{
		std::remove("level.txt");
	}

	boardFile.open("level.txt");
	
	// try and catch
	if (boardFile.is_open())
	{
		saveBoardAndCopyToText(boardFile, score, levelTime);
		//levelExists = true;
	}
}

//---------------------------------------------------------------------------------------
void Board::saveBoardAndCopyToText(std::ofstream& boardFile, int score, float levelTime)const
{
	std::string info;

	info = std::to_string(levelTime) + " " + std::to_string(score)+ "\n";
	boardFile << info;

	for (auto it = m_sticks.begin(); it != m_sticks.end(); it++)
	{
		info = it->getStickInfo();
		boardFile << info;
	}

}
//-----------------------------------------------------------------------------
int Board::getNumOfSticks()const
{
	return m_sticks.size();
}


