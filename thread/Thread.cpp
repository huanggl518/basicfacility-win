#include "Thread.h"
#include <cassert>
#include "CmmHdr.h"

Thread::Thread(ThreadPriority priority /*=PRIORITY_NORMAL*/)
: m_priority(priority), m_active(false), m_terminated(false)
{
  m_hThrd = chBEGINTHREADEX(NULL, 0,
	  threadProc, this, CREATE_SUSPENDED, &m_thrdID);
	if (m_hThrd == NULL) {
		throw ::GetLastError();
	}
  
  assert(m_hThrd);
	setPriority(priority);
}


Thread::~Thread()
{
  ::CloseHandle(m_hThrd);
}

bool Thread::suspend()
{
  AutoLock lock(&m_lock);
  if (m_active) 
    m_active = !(::SuspendThread(m_hThrd) != (DWORD)-1);
  return (!m_active);
}

bool Thread::resume()
{
  AutoLock lock(&m_lock);
  if (!m_active) 
    m_active = (::ResumeThread(m_hThrd) != (DWORD)-1);
  return m_active;
}

bool Thread::exec()
{
  return resume();
}

bool Thread::wait()
{
  AutoLock lock(&m_lock);
  m_active = !(::WaitForSingleObject(m_hThrd, INFINITE) != WAIT_FAILED);
  return (!m_active);
}

void Thread::terminate()
{
  if (!m_terminated) {
    m_terminated = true;
    onTerminate();
  }
}

DWORD WINAPI Thread::threadProc(LPVOID lpArg)
{
  Thread *pthis = static_cast<Thread*>(lpArg);
  try {
    pthis->run();
  }
  catch (...) {

  }

  pthis->m_active = false;

  return 0;
}

bool Thread::setPriority(ThreadPriority pri)
{
  int priority;

  switch(pri)
  {
  case PRIORITY_IDLE:
    priority = THREAD_PRIORITY_IDLE;
    break;
  case PRIORITY_LOWEST:
    priority = THREAD_PRIORITY_LOWEST;
    break;
  case PRIORITY_BELOW_NORMAL:
    priority = THREAD_PRIORITY_BELOW_NORMAL;
    break;
  case PRIORITY_NORMAL:
    priority = THREAD_PRIORITY_NORMAL;
    break;
  case PRIORITY_ABOVE_NORMAL:
    priority = THREAD_PRIORITY_ABOVE_NORMAL;
    break;
  case PRIORITY_HIGHEST:
    priority = THREAD_PRIORITY_HIGHEST;
    break;
  case PRIORITY_TIME_CRITICAL:
    priority = THREAD_PRIORITY_TIME_CRITICAL;
    break;
  default:
    priority = THREAD_PRIORITY_NORMAL;
  }

  return SetThreadPriority(m_hThrd, priority) != 0;
}

void Thread::onTerminate()
{

}