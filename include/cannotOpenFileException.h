#include <exception>

class cannotOpenFileException : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{

	}
};