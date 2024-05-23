#include <exception>
#include <string>

class WrongInputException : public std::exception
{
public:
	WrongInputException() = default;
	virtual const char* what() const noexcept override { return "Invalid input detected in the file\n wrong data in the fields.\n"; };
};