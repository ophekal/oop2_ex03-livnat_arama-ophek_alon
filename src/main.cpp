
#include <iostream>
#include <exception>
#include "Menu.h"

//---------------------------------------------------------------

int main()
{
	try
	{
		Menu menu;
		menu.run();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}
