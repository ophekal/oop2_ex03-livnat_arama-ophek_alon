#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.h"
#include "InfoBar.h"
#include "Clock.h"
#include "Macros.h"

class Controller
{
public:
	Controller() = default;
	void run(sf::RenderWindow& window, bool& load, bool& musicOn);
	void setData(float time, int score, int sticksPicked);
	void print(sf::RenderWindow& window);
	void setScore(int score);
	void incStickPicked();
	void setRemovable(int removable);
	void decSticksLeft();

private:
	void startGame(sf::RenderWindow& window, bool load, bool& musicOn);
	void windowPollEvent(sf::RenderWindow& window, bool& musicOn);
	void handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow& window, bool& musicOn);
	void handleClickBoard(sf::RenderWindow& window, const sf::Vector2f& location);
	void handleClickInfoBar(sf::RenderWindow& window, const sf::Vector2f& location, bool& musicOn);
	void updateInfoBar(bool& musicOn);
	void printFinalScore(sf::RenderWindow& window);


	Board m_board;
	InfoBar m_infoBar;
	Clock m_clock;

	float m_levelTime = 0;
	bool m_levelOver = false;
	int m_totalScore = 0;

	int m_sticksPicked = 0;
	int m_removableSticks;
	int m_sticksLeft;
};