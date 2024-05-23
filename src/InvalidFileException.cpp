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

}