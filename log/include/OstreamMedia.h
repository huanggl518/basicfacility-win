#ifndef OSTREAMMEDIA_H
#define OSTREAMMEDIA_H

#include <string>
#include <queue>
#include "LogMedia.h"

class OstreamMedia : public LogMedia
{
public:
	OstreamMedia();
	virtual ~OstreamMedia();

  virtual size_t write(ulong threadId, int priority, const std::string &message);

private:
	std::queue<std::string> m_qLog;
};

#endif // OSTREAMMEDIA_H
