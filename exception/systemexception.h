#ifndef SYSTEMEXCEPTION_H
#define SYSTEMEXCEPTION_H

#include <string>
#include <Windows.h>

class SystemException
{
public:
	SystemException();
	SystemException(DWORD errCode);
	SystemException(const std::string &userMessage);
	SystemException(DWORD errCode, const std::string &userMessage);
	~SystemException();

	inline const std::string& getMessage() const
	{
		return m_errString;
	}

private:
	void createMessage(DWORD errCode, const std::string &userMessage);

	DWORD m_errCode;
	std::string m_errString;
};

#endif // SYSTEMEXCEPTION_H