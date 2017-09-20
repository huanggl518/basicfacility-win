#include "FileMedia.h"
#include <cassert>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif // _WIN32
#include <fcntl.h>
#include "LogLayout.h"

using namespace std;
FileMedia::FileMedia(const string &fileName, bool append) 
{
	assert(fileName.size());

#ifdef _WIN32
  int flag = ((append) ? _O_APPEND : _O_TRUNC) | _O_CREAT | _O_WRONLY;
  m_fd = ::_open(fileName.c_str(), flag);
#else
  int flag = ((append) ? O_APPEND : O_TRUNC) | O_CREAT | O_WRONLY;
  m_fd = ::open(fileName.c_str(), flag, S_IRUSR | S_IWUSR);
#endif
}


FileMedia::~FileMedia()
{
#ifdef _WIN32
  ::_close(m_fd);
#else
  ::close(m_fd);
#endif // _WIN32
}


size_t FileMedia::write(ulong threadId, int priority, const std::string &message)
{
  string logMsg = LogLayout::format(threadId, priority, message);
#ifdef _WIN32
  size_t bytesWritten = ::_write(m_fd, logMsg.c_str(), logMsg.length());
#else
  size_t bytesWritten = ::write(m_fd, logMsg.c_str(), logMsg.length());
#endif // _WIN32

	return bytesWritten;
}
