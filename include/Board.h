
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <list>
#include "HandleResources.h"
#include "Stick.h"

class Controller;


class Board
{
public:
	Board();
	void readTheLevelAndUpdateData(Controller& controller, bool load);
	//void updateBoard();
	void printBoard(sf::RenderWindow& window);
	//void clear();
	//void reset();
	void loadAndRunFromExisting(Controller& controller);
	void generateGame(Controller& controller);
	void createRandomStick();
	void updateControllerData(Controller& controller, float time, int score) const;
	void addStickToList(Stick& stick/*StickType colour, float angle, float len, float x, float y*/);
	void handlePressedSave(int scorefloat, float levelTime)const;
	void handlePressedHint();
	void saveBoardAndCopyToText(std::ofstream& boardFile, int score, float levelTime)const;
	//void updateSticksList(auto needToRemoveIt);
	void updateRemoveable();
	int getRemovableSticks()const;
	int getNumOfSticks()const;
	//void deleteStick(auto needToRemoveIt);

private:

	sf::RectangleShape m_board;    // for the background
	std::list<Stick> m_sticks;
	std::multimap<int, Stick*> m_removeable;


	float randomFloat(float min, float max) const;

};

