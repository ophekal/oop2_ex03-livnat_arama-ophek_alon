
#include "Board.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Macros.h"
#include <filesystem>
#include "Stick.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Controller.h"

//-------------------------------------------------------------------------------------
Board::Board()
	: m_board(sf::Vector2f(BOARD_HIG, BOARD_WID))
{
	m_board.setPosition({ BOARD_START_X ,BOARD_START_Y });
	m_board.setTexture(HandleResources::instance().getBackgroundTexture(B_BOARD));
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
					float angle, x, y;
					int colour, len;
					if (!(iss >> colour >> angle >> len >> x >> y))
					{
						//throw  worng input, if range isn't good, x-y arent goot etc
					}
					addStickToList(StickType(colour), angle, len, x, y);
					firstLine = false;
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
void Board::generateGame(Controller& controller) const
{
	//auto colour = srand
}

//-------------------------------------------------------------------------------------
//This function is responsible of updating the data according to what was saved in the
//existing file
void Board::updateControllerData(Controller& controller, float time, int score) const
{
	controller.setData(time, score);
}

//-------------------------------------------------------------------------------------
//This function is responsible of adding the stick to the list of sticks
void Board::addStickToList(StickType colour, float angle, int len, float x, float y)
{
	sf::Vector2f point(x,y);
	Stick stick(HandleResources::instance().getObjectTexture(colour), Colour(colour), angle, point, len);
	
	m_sticks.push_back(stick);
	
	//go over all the prev sticks and check if this stick block them
	for (auto it = m_sticks.begin(); it != std::prev(m_sticks.end()); it++)
	{
		if (stick.checkAndUpdateIntersection(*it))
		{
			it->updateSticksBlocked(&stick);
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
