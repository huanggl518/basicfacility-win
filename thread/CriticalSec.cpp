#include "CriticalSec.h"


CriticalSec::CriticalSec(void)
{
  ::InitializeCriticalSection(&m_cs);
}

CriticalSec::~CriticalSec(void)
{
  ::DeleteCriticalSection(&m_cs);
}

void CriticalSec::lock()
{
  ::EnterCriticalSection(&m_cs);
}

void CriticalSec::unlock()
{
  ::LeaveCriticalSection(&m_cs);
}