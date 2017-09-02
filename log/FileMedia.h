#ifndef FILEMEDIA_H
#define FILEMEDIA_H

#include <vector>
#include "LogMedia.h"

class FileMedia : public LogMedia
{
public:
	explicit FileMedia(const std::string &filename, bool append = true);
	~FileMedia();

  virtual size_t write(ulong threadId, int priority, const std::string &message);

private:
	int m_fd;
};

#endif // FILEMEDIA_H
