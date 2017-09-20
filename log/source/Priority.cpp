#include "Priority.h"



Priority::Priority()
{
}


Priority::~Priority()
{
}


const std::string& Priority::getPriorityName(int priority)
{
	static const std::string priorityNames[] = {
		"fatal",
		"error",
		"warning",
		"info",
		"debug"
	};

	return priorityNames[priority / 100];
}