#ifndef LOCKABLE_H
#define LOCKABLE_H

class Lockable
{
public:
  virtual ~Lockable();
  virtual void lock() = 0;
  virtual void unlock() = 0;
};

#endif // LOCKABLE_H
