
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
	void readTheLevelAndUpdateData(Controller& controller, bool& load);
	void printBoard(sf::RenderWindow& window);
	void handlePressedSave(int scorefloat, float levelTime, int sticksPicked) const;
	void handlePressedHint(sf::RenderWindow& window, Controller& controller);
	int getRemovableSticks()const;
	int getNumOfSticks()const;
	void checkIfPressedOnStick(sf::RenderWindow& window, Controller& controller, const sf::Vector2f& location);

private:
	void loadAndRunFromExisting(Controller& controller, bool& load);
	void generateGame(Controller& controller);
	void createRandomStick();
	void updateControllerData(Controller& controller, float time, int score, int sticksPicked) const;
	void addStickToList(Stick& stick);
	float randomFloat(float min, float max) const;
	void saveBoardAndCopyToText(std::ofstream& boardFile, int score, float levelTime, int sticksPicked)const;
	void updateDataAndDeleteStick(std::list<Stick>::reverse_iterator& needToRemoveIt);
	void updateRemoveable();
	void deleteStick(std::list<Stick>::reverse_iterator& needToRemoveIt);
	void highlightBlockingSticks(sf::RenderWindow& window, Controller& controller, Stick& stick);


	sf::RectangleShape m_board;    // for the background
	std::list<Stick> m_sticks;
	std::multimap<int, Stick*> m_removeable;
};

