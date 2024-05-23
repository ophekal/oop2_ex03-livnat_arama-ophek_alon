#include <exception>
#include <string>

class InvalidFileException : public std::exception
{
public:
	InvalidFileException(std::string name);
	virtual const char* what() const noexcept override;

private:
	std::string m_fileName;
};