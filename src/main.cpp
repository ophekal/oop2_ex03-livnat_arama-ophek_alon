
#include "Menu.h"
#include <iostream>
#include <exception>

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
