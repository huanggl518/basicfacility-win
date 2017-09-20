#ifndef PRIORITY_H
#define PRIORITY_H

#include <string>

class Priority
{
public:
	enum LogPriority { 
         LOG_FATAL    = 0,
				 LOG_ERROR    = 100,
				 LOG_WARNING  = 200,
	       LOG_INFO     = 300,
	       LOG_DEBUG    = 400};

	Priority();
	~Priority();

	static const std::string& getPriorityName(int priority);
};

#endif // PRIORITY_H

