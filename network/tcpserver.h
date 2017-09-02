#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "ipv4socket.h"
#include "../thread/Thread.h"

class TcpServer// : public Thread
{
public:
  TcpServer(const char *host, unsigned short port);
  TcpServer(const Ipv4Endpoint &endpoint);
  virtual ~TcpServer();

protected:
  virtual void run() = 0;
  virtual void newSocketAccepted(Ipv4Socket *pSocket) = 0;

  Ipv4Socket m_socket;
};

#endif // TCPSERVER_H
