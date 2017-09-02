#include "SystemException.h"



SystemException::SystemException()
	: m_errCode(::GetLastError())
{
	createMessage(m_errCode, std::string(""));
}


SystemException::SystemException(DWORD errCode)
	: m_errCode(errCode)
{
	createMessage(m_errCode, std::string(""));
}


SystemException::SystemException(const std::string &userMessage)
	: m_errCode(ERROR_SUCCESS)
{
	createMessage(m_errCode, userMessage);
}


SystemException::SystemException(DWORD errCode, const std::string &userMessage)
	: m_errCode(errCode)
{
	createMessage(m_errCode, userMessage);
}


SystemException::~SystemException()
{
}


void SystemException::createMessage(DWORD errCode, const std::string &userMessage)
{
	if (errCode == ERROR_SUCCESS && userMessage.length() == 0)
	{
		m_errString = "Thrown a system exception but the program"
			" cannot identify the corresponding system error.";

		return;
	}
	
	HLOCAL hlocal = NULL;
	DWORD	systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	BOOL fOk = ::FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, errCode, systemLocale,
		(PTSTR)&hlocal, 0, NULL);

	if (!fOk) 
	{
		HMODULE hDll = LoadLibraryEx(TEXT("netmsg.dll"), NULL,
			DONT_RESOLVE_DLL_REFERENCES);
		if (hDll != NULL) 
		{
			fOk = FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
				FORMAT_MESSAGE_ALLOCATE_BUFFER,
				hDll, errCode, systemLocale,
				(PTSTR)&hlocal, 0, NULL);
			FreeLibrary(hDll);
		}
	}

	if (fOk && (hlocal != NULL))
	{
		m_errString = (char*)::LocalLock(hlocal);
		::LocalFree(hlocal);
	}
}