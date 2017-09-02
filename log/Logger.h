#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>

#include "Priority.h"

class LogMedia;

class Logger
{
public:
	Logger();
	~Logger();

	inline void addMedia(LogMedia *logMedia) {
		m_mediaList.push_back(logMedia);
	}

	void removeMedia(LogMedia *logMedia);

	void setPriority(Priority::LogPriority priority);

  void info(const std::string &message);
	void info(const char *message, ...);

	void debug(const std::string &message);
	void debug(const char *message, ...);

	void warning(const std::string &message);
	void warning(const char *message, ...);

	void error(const std::string &message);
	void error(const char *format, ...);

	void fatal(const std::string &message);
	void fatal(const char *format, ...);
	
protected:
	inline bool isAllowed2Log(Priority::LogPriority priority) const {
		return (priority <= m_priority);
	}

	void logMessage(Priority::LogPriority priority, const std::string &message);

private:
	Priority::LogPriority m_priority;
	std::vector<LogMedia*> m_mediaList;
};

#endif // LOGGER_H
