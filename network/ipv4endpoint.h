#ifndef IPV4_ENDPOINT_H
#define IPV4_ENDPOINT_H

//#include <arpa/inet.h>
#include <string>

#ifdef _WIN32
#include <WinSock2.h>
#define socklen_t int
#endif

class Ipv4Endpoint
{
public:
  Ipv4Endpoint(unsigned short port);
  Ipv4Endpoint(const char *host, unsigned short port);
  Ipv4Endpoint(struct sockaddr_in sockAddr);

  struct sockaddr_in socketAddr() const;

  inline socklen_t addrLen() const
  {
    return sizeof(struct sockaddr_in);
  }

protected:
  unsigned short m_port;
  struct in_addr m_addr;
};

#endif // Ipv4Endpoint
