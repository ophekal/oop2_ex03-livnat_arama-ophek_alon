#include <exception>
#include <string>

class InvalidFileException : public std::exception
{
public:
	InvalidFileException() = default;
	virtual const char* what() const noexcept override { return "The file doesn't exists.\n"; }
};