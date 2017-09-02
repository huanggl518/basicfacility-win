#include "AutoLock.h"

AutoLock::AutoLock(Lockable *lockable)
    : m_lockable(lockable)
{
    m_lockable->lock();
}

AutoLock::AutoLock(const Lockable *lockable) 
: m_lockable(const_cast<Lockable*>(lockable))
{
  m_lockable->lock();
}

AutoLock::~AutoLock()
{
    m_lockable->unlock();
}