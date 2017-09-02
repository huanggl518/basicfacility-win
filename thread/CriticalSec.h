#ifndef CRITICAL_SEC_H
#define CRITICAL_SEC_H

#include "Lockable.h"
#include <Windows.h>


class CriticalSec : public Lockable
{
public:
  CriticalSec(void);
  virtual ~CriticalSec(void);

  virtual void lock();
  virtual void unlock();

private:
  CRITICAL_SECTION m_cs;
};

#endif // CRITICAL_SEC_H

