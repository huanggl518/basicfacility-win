#include "Logger.h"
#include <stdarg.h>
#include "LogMedia.h"
#include "../thread/thread.h"

using namespace std;
Logger::Logger()
	: m_priority(Priority::LOG_DEBUG)
{
}


Logger::~Logger()
{
}


void Logger::removeMedia(LogMedia *logMedia)
{
	std::vector<LogMedia*>::iterator it;

	for (it = m_mediaList.begin(); it != m_mediaList.end(); ++it)
		if ((*it) == logMedia) {
			m_mediaList.erase(it);
			break;
		}
}


void Logger::setPriority(Priority::LogPriority priority)
{
	m_priority = priority;
}


void Logger::info(const char *message, ...)
{
	va_list ap;
	char buffer[1024];

	va_start(ap, message);

	vsprintf(buffer, message, ap);
	info(string(buffer));

	va_end(ap);
}


void Logger::info(const string &message)
{
	logMessage(Priority::LOG_INFO, message);
}


void Logger::debug(const char *message, ...)
{
	va_list ap;
	char buff[1024];

	va_start(ap, message);

	vsprintf(buff, message, ap);
	debug(string(buff));

	va_end(ap);
}

void Logger::debug(const std::string &message)
{
	logMessage(Priority::LOG_DEBUG, message);
}


void Logger::warning(const char *message, ...)
{
	va_list ap;
	char buffer[1024];

	va_start(ap, message);

	vsprintf(buffer, message, ap);
	warning(string(buffer));

	va_end(ap);
}


void Logger::warning(const std::string &message)
{
	logMessage(Priority::LOG_WARNING, message);
}


void Logger::error(const char *message, ...)
{
	va_list ap;
	char buffer[1024];

	va_start(ap, message);

	vsprintf(buffer, message, ap);
	error(string(buffer));

	va_end(ap);
}


void Logger::error(const string &message)
{
	logMessage(Priority::LOG_FATAL, message);
}


void Logger::fatal(const char *message, ...)
{
	va_list ap;
	char buffer[1024];

	va_start(ap, message);

	vsprintf(buffer, message, ap);
	fatal(string(buffer));

	va_end(ap);
}


void Logger::fatal(const std::string &message)
{
	logMessage(Priority::LOG_FATAL, message);
}


void Logger::logMessage(Priority::LogPriority priority, const std::string &message)
{
	std::vector<LogMedia*>::iterator it;

	if (!isAllowed2Log(priority))
		return;

	for (it = m_mediaList.begin(); it != m_mediaList.end(); ++it)
    (*it)->write(Thread::threadSelf(), priority, message);
}
