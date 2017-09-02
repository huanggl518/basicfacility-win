#ifndef WIN_COMM_H
#define WIN_COMM_H
#include <process.h>

typedef unsigned(__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStackSize, pfnStartAddr, \
  pvParam, dwCreateFlags, pdwThreadId)                 \
  ((HANDLE)_beginthreadex(\
  (void *)(psa), \
  (unsigned)(cbStackSize), \
  (PTHREAD_START)(pfnStartAddr), \
  (void *)(pvParam), \
  (unsigned)(dwCreateFlags), \
  (unsigned *)(pdwThreadId)))

#endif // WIN_COMM_H