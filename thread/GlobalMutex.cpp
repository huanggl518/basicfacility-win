#include "GlobalMutex.h"
#include <iostream>

GlobalMutex::GlobalMutex(const TCHAR *name)
{
  m_mutex = ::CreateMutex(NULL, FALSE, name);
  if (m_mutex == 0)
    throw ::GetLastError();
  else if (::GetLastError() == ERROR_ALIAS_EXISTS)
    std::printf("Mutex already exists\n");
}

GlobalMutex::~GlobalMutex()
{
  ::CloseHandle(m_mutex);
}

void GlobalMutex::lock()
{
  ::WaitForSingleObject(m_mutex, INFINITE);
}

void GlobalMutex::unlock()
{
  ::ReleaseMutex(m_mutex);
}