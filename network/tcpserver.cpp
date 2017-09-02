#include "tcpserver.h"

TcpServer::TcpServer(const char *host, unsigned short port)
{
  m_socket.bind(host, port);
  m_socket.listen();
}


TcpServer::TcpServer(const Ipv4Endpoint &endpoint)
{
  m_socket.bind(endpoint);
  m_socket.listen();
}


TcpServer::~TcpServer()
{

}

