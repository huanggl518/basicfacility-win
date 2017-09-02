#include "QueueMedia.h"
#include "LogLayout.h"



QueueMedia::QueueMedia()
{
}


QueueMedia::~QueueMedia()
{
	while (m_qLogMessage.size())
		m_qLogMessage.pop();
}


size_t QueueMedia::write(ulong threadId, int priority, const std::string &message)
{
  std::string logMessage = LogLayout::format(threadId, priority, message);
	
	m_qLogMessage.push(logMessage);

	return logMessage.length();
}


std::ostream& operator<<(std::ostream& out, QueueMedia &log)
{
	size_t logNum = log.m_qLogMessage.size();

	for (size_t i = 0; i < logNum; ++i) {
		std::cout << log.m_qLogMessage.front();
		log.m_qLogMessage.pop();
	}

	return out;
}
