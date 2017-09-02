#include "ipv4endpoint.h"
#include "../exception/systemexception.h"

Ipv4Endpoint::Ipv4Endpoint(unsigned short port)
  : m_port(htons(port))
{
  m_addr.s_addr = INADDR_ANY;
}

Ipv4Endpoint::Ipv4Endpoint(const char *host, unsigned short port)
  : m_port(htons(port))
{
  m_addr.s_addr = inet_addr(host);
}

struct sockaddr_in Ipv4Endpoint::socketAddr() const
{
  struct sockaddr_in saddr;

  saddr.sin_family = AF_INET;
  saddr.sin_addr = m_addr;
  saddr.sin_port = m_port;

  return saddr;
}
