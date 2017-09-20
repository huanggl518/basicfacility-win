#ifndef LOGMEDIA_H
#define LOGMEDIA_H

#include <string>
#include "../customtype.h"

class LogMedia
{
public:
	LogMedia();
	virtual ~LogMedia();

  virtual size_t write(ulong threadId, int priority, const std::string &message) = 0;
};

#endif // LOGMEDIA_H
