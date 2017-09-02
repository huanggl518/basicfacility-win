#include "OstreamMedia.h"
#include <iostream>
#include "LogLayout.h"


OstreamMedia::OstreamMedia()
{
}


OstreamMedia::~OstreamMedia()
{
}


size_t OstreamMedia::write(ulong threadId, int priority, const std::string &message)
{
  std::string logMsg = LogLayout::format(threadId, priority, message);

	std::cout << logMsg;

	return logMsg.length();
}
