#include "ipv4socket.h"
#include <sys/types.h>
#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/tcp.h>
#endif
#include "../exception/systemexception.h"


Ipv4Socket::Ipv4Socket()
  : m_endpoint(NULL)
{
  m_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (m_socket == -1)
    throw SystemException();
}

Ipv4Socket::Ipv4Socket(int socket)
  : m_socket(socket)
{

}

void Ipv4Socket::connect(const char *host, unsigned short port)
{
  Ipv4Endpoint endpoint(host, port);

  connect(endpoint);
}


void Ipv4Socket::connect(const Ipv4Endpoint &endpoint)// throw(SystemException)
{
  struct sockaddr_in addr = endpoint.socketAddr();

  if (::connect(m_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    throw SystemException();
}


void Ipv4Socket::bind(const char *host, unsigned short port)// throw(SystemException)
{
  Ipv4Endpoint endpoint(host, port);

  bind(endpoint);
}


void Ipv4Socket::bind(const Ipv4Endpoint &endpoint)// throw(SystemException)
{
  if (m_endpoint == NULL)
    m_endpoint = new Ipv4Endpoint(endpoint);

  struct sockaddr_in addr = endpoint.socketAddr();

  if (::bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    throw SystemException();
}


void Ipv4Socket::listen(int backlog)// throw(SystemException)
{
  if (backlog == 0)
    backlog = 5;

  if (::listen(m_socket, backlog) == -1)
    throw SystemException();
}


Ipv4Socket* Ipv4Socket::accept()// throw(SystemException)
{
  struct sockaddr_in addr;
  socklen_t addrlen = sizeof(addr);
  int socket;

  socket = ::accept(m_socket, (struct sockaddr *)&addr, &addrlen);
  if (socket == -1)
    throw SystemException();

  Ipv4Socket *accepted = new Ipv4Socket(socket);

  return accepted;
}


int Ipv4Socket::write(const char *data, size_t len, int flags)// throw(SystemException)
{
  int result = ::send(m_socket, data, len, flags);

  if (result == -1)
    throw SystemException();

  return result;
}


int Ipv4Socket::read(char *buff, size_t size, int flags)// throw(SystemException)
{
  int result = ::recv(m_socket, buff, size, flags);

  if (result == -1)
    throw SystemException();

  if (result == 0)
    throw SystemException(0, "Connection has been gracefully shutdown by peer.");

  return result;
}


void Ipv4Socket::setSocketOptions(int level, int name, void *value, socklen_t len)// throw(SystemException)
{
  if (::setsockopt(m_socket, level, name, static_cast<char*>(value), len) == -1)
    throw SystemException();
}


void Ipv4Socket::getSocketOptions(int level, int name, void *value, socklen_t &len)// throw(SystemException)
{
  if (::getsockopt(m_socket, level, name, static_cast<char*>(value), &len) == -1)
    throw SystemException();
}


void Ipv4Socket::setTcpNoDelay(bool enabled)// throw(SystemException)
{
  setSocketOptions(IPPROTO_TCP, TCP_NODELAY, &enabled, sizeof(enabled));
}


void Ipv4Socket::setExclusiveAddrUse()// throw(SystemException)
{
  int val = 0;

  setSocketOptions(SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

void Ipv4Socket::close()// throw(SystemException)
{
#ifdef _WIN32
  if (::closesocket(m_socket) == -1)
#else
  if (::close(m_socket) == -1)
#endif
    throw SystemException();
}
