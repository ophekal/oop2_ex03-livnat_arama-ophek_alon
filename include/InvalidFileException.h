#include <exception>

class invalidFileException : public std::exception
{
public:
	//invalidFileException(char* name);
	//virtual const char* what() const noexcept override;

private:
	//char* m_fileName;
};