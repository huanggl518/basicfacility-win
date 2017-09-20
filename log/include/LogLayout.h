#ifndef LOGLAYOUT_H
#define LOGLAYOUT_H

#include <string>
#include "../customtype.h"

class LogLayout
{
public:
	LogLayout();
	~LogLayout();

  static std::string format(ulong threadID, int priority, const std::string &message);
};

#endif // LOGLAYOUT_H

