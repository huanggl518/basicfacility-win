#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include "../customtype.h"
#include "AutoLock.h"
#include "CriticalSec.h"

class Thread
{
public:
  enum ThreadPriority {
    PRIORITY_IDLE,
    PRIORITY_LOWEST,
    PRIORITY_BELOW_NORMAL,
    PRIORITY_NORMAL,
    PRIORITY_ABOVE_NORMAL,
    PRIORITY_HIGHEST,
    PRIORITY_TIME_CRITICAL
  };

public:
  Thread(ThreadPriority priority = PRIORITY_NORMAL);
  virtual ~Thread();

  bool exec();
  bool suspend();
  bool resume();
  bool setPriority(ThreadPriority priority);
  bool wait();
  /* User wait() after terminated() */
  void terminate();
  inline bool isActive() const
  {
    return m_active;
  }

  inline bool isTerminated() const
  {
    return m_terminated;
  }

  inline DWORD thrdID() const
  {
    return m_thrdID;
  }

  static ulong threadSelf()
  {
    return ::GetCurrentThreadId();
  }

protected:
  virtual void onTerminate();
  virtual void run() = 0;

private:
  static DWORD WINAPI threadProc(LPVOID lpArg);

  ThreadPriority m_priority;
  CriticalSec m_lock;
  volatile bool m_active;
  volatile bool m_terminated;
  DWORD m_thrdID;
  HANDLE m_hThrd;
};

#endif //THREAD_H