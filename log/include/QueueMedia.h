#ifndef QUEUEMEDIA_H
#define QUEUEMEDIA_H

#include "LogMedia.h"
#include <queue>
#include <iostream>
#include <string>

class QueueMedia : public LogMedia
{
public:
	QueueMedia();
	virtual ~QueueMedia();

  virtual size_t write(ulong threadId, int priority, const std::string &message);
	
	friend std::ostream& operator<<(std::ostream&, QueueMedia&);

private:
	std::queue<std::string> m_qLogMessage;
};

#endif // QUEUEMEDIA_H
