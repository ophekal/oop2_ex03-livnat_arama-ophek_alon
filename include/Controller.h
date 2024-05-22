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
	//void handleWindow(sf::RenderWindow& window, bool& musicOn);

private:

	Board m_board;
	InfoBar m_infoBar;
	Clock m_clock;

	float m_levelTime = 0;
	bool m_levelOver = false;
	int m_totalScore = 0;

	int m_sticksPicked = 0;
	int m_removableSticks;
	int m_sticksLeft;

	void startGame(sf::RenderWindow& window, bool load, bool& musicOn);
	void windowPollEvent(sf::RenderWindow& window, bool& musicOn);
	void print(sf::RenderWindow& window);
	/*void printFeedback(const sf::Texture& feedback, sf::RenderWindow& window,
		const sf::Sprite& background, GameSound sound)const;
	bool checkGameStatus(int numOfCheese, int numOfCats, sf::RenderWindow& window,
		const sf::Sprite& background, bool& musicOn);
	bool checkLevelStatus(int numOfCheese, int numOfCats, sf::RenderWindow& window,
		const sf::Sprite& background, bool& musicOn);
	void updateGameBackground(const sf::RenderWindow& window, sf::Sprite& background);
	void moveMouse(sf::Time deltaTime);
	void moveCats(sf::Time deltaTime);
	void handleLevelOver(sf::RenderWindow& window, const sf::Sprite& background, bool& musicOn);
	void handleExit(sf::RenderWindow& window, const sf::Sprite& background);*/
	void handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow& window, bool& musicOn);
	void handleClickBoard(const sf::Vector2f& location);
	void handleClickInfoBar(const sf::Vector2f& location, bool& musicOn);
	void updateInfoBar(bool& musicOn);
	void printFinalScore(sf::RenderWindow& window);
};