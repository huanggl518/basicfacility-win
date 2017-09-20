#include "LogLayout.h"
#include <sys/timeb.h>
#include <time.h>
#include <sstream>
#include "Priority.h"


LogLayout::LogLayout()
{
}


LogLayout::~LogLayout()
{
}


std::string LogLayout::format(ulong threadId, int priority, const std::string &message)
{
	struct timeb tb;
	struct tm *lt;

	::ftime(&tb);
	lt = ::localtime(&tb.time);
	
	char logStr[1024];
  sprintf(logStr, "%d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d %lu %s: %s",
		lt->tm_year + 1900, lt->tm_mon, lt->tm_mday,
    lt->tm_hour, lt->tm_min, lt->tm_sec, tb.millitm, threadId,
		Priority::getPriorityName(priority).c_str(), message.c_str());

	return logStr;
}
