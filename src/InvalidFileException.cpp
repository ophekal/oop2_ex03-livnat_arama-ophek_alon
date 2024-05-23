#include "InvalidFileException.h"
#include <string>

//-----------------------------------------------------------------------------
InvalidFileException::InvalidFileException(std::string name)
{
	m_fileName = name;
}
//-----------------------------------------------------------------------------
const char* InvalidFileException::what() const noexcept
{
	std::string myString = "The file: " + m_fileName + " doesn't exists";
	const char* charPtr = myString.c_str();
	return charPtr;
}