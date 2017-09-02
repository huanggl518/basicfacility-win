#ifndef GLOBAL_MUTEX_H
#define GLOBAL_MUTEX_H

#include <Windows.h>
#include "Lockable.h"

class GlobalMutex : public Lockable
{
public:
  GlobalMutex(const TCHAR *name);
  virtual ~GlobalMutex();
  
  virtual void lock();
  virtual void unlock();

private:
  HANDLE m_mutex;
};

#endif // GLOBAL_MUTEX_H
