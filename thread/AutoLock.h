#ifndef AUTO_LOCK_H
#define AUTO_LOCK_H

#include "Lockable.h"

class AutoLock
{
public:
  AutoLock(Lockable *lockable);

  // for inline lock. like:
  // AutoLock lock(&lockable);
  AutoLock(const Lockable *lockable); 
  ~AutoLock();
    
private:
  Lockable *m_lockable;
};

#endif // AUTO_LOCK_H