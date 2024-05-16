#pragma once
#include <SFML/Graphics.hpp>

const int INFOBAR_TEXT_SIZE = 30;
const int SCORE_TEXT_SIZE = 80;


enum StickType
{
	S_BLACK_STICK,
	S_RED_STICK,
	S_BLUE_STICK,
	S_GREEN_STICK,
	S_YELLOW_STICK
};

enum Background
{
	B_MENU,
	B_BOARD,
	B_EXIT,
	B_START,
	B_RULES,
	B_LOAD,
	B_GAMERULES,
	B_SOUND,
	B_MUTE
};

enum MenuButton
{
	M_START,
	M_EXIT,
	M_LOAD,
	M_SOUND,
	M_RULES
};


//enum Screen
//{
//	S_WIN,
//	S_GAMEOVER,
//	S_FINALSCORE
//};

enum Colour
{
	C_BLACK,
	C_RED,
	C_BLUE,
	C_GREEN,
	C_YELLOW
};

//-----------scores-----------
const int BLACK = 25;
const int RED = 10;
const int BLUE = 5;
const int GREEN = 2;
const int YELLOW = 1;

//------------menu------------
const int WINDOW_HEIGHT = 950;//1070;
const int WINDOW_WIDTH = 1500;
const float START_X = 550;
const float START_Y = 300;
const float LOAD_X = 550;
const float LOAD_Y = 450;
const float RULES_X = 550;
const float RULES_Y = 600;
const float EXIT_X = 550;
const float EXIT_Y = 750;
const float SOUND_X = 1385;
const float SOUND_Y = 42;

const float GAMERULES = 726;

const sf::Vector2f BUTTON_SIZE = { 400,100 };
const sf::Vector2f SOUND_SIZE = { 65,65 };

//------------board------------
const float BOARD_HIG = 950;
const float BOARD_WID = 1050;
const float BOARD_START_X = 450;
const float BOARD_START_Y = 0;

//----------infoBar-------------

enum Bar
{
	B_TIME,
	B_INFO,
	B_PICKEDUP,
	B_FREE,
	B_HOME,
	B_SCORE,
	B_SAVE
	//B_RESTART
};

const sf::Vector2f INFO_SIZE = { 300,110 };

const float INFO_X = 50;
const float INFO_Y = 50;
const float CLOCK_Y = 190;
const float LEVEL_Y = 330;
const float LIVES_Y = 470;
const float KEYS_Y = 610;
const float SCORE_Y = 750;


const float I_SOUND_X = 50;
const float I_SOUND_Y = 900;
const float HOME_X = 167.5;
const float HOME_Y = 900;
const float RESTART_X = 285;
const float RESTART_Y = 900;


const float LONG_LEVEL = (3 * 60) + 1;
const float SHORT_LEVEL = ((1.5) * 60) + 1;

//----------------sounds-----------

enum GameSound
{
	G_FREE,
	G_BLOCKED,
	G_WIN,
	G_LOST
};