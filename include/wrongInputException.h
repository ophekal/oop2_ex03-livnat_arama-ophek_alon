#include <exception>
#include <string>

class WrongInputException : public std::exception
{
public:
	WrongInputException() = default;
	virtual const char* what() const noexcept override { return "Invalid input in one of the fields in the file.\n"; };
};