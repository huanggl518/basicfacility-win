#ifndef IPV4SOCKET_H
#define IPV4SOCKET_H

#include "ipv4endpoint.h"
//#include "exception/systemexception.h"

class Ipv4Socket
{
public:
  /* Create a new socket.
   */
  Ipv4Socket();

  /* Connect to a remote host.
   * @param host host to connect.
   * @param port port to connect.
   * @throws SystemException on fail.
   */
  void connect(const char *host, unsigned short port)/* throw(SystemException)*/;

  /* Connect to a remote host.
   * @param endpoint host to connect.
   * @throws SystemException on fail.
   */
  void connect(const Ipv4Endpoint &endpoint); //throw(SystemException);

  /* Bind socket to a endpoint.
   * @param host to bind.
   * @param port to bind.
   * @throws SystemException on fail.
   */
  void bind(const char *host, unsigned short port);// throw(SystemException);

  /* Bind socket to a endpoint.
   * @param address to bind.
   * @throws SystemException on fail.
   */
  void bind(const Ipv4Endpoint &endpoint);// throw(SystemException);

  /* Listen on address for connections.
   * @param backlog max count of connections in pool.
   * @throws SystemException on fail.
   */
  void listen(int backlog = 5);// throw(SystemException);

  /* Accept new connections
   * @throws SystemExceptions on fail.
   * @return a newly created socket which client is responsible to destroy
   */
  Ipv4Socket* accept();// throw(SystemException);

  /* Send date.
   * @param data to send.
   * @param len length of the data.
   * @param flags of socket.
   * @return the bytes sent.
   */
  int write(const char *data, size_t len, int flags = 0);// throw(SystemException);

  /* Read data.
   * @param buff buffer to recv data.
   * @param size  bytes of data to receive.
   * @param flags socket flags
   * @return bytes received.
   */
  int read(char *buff, size_t size, int flags = 0);// throw(SystemException);

  /* Set socket options.
   * @params same to ::setsockopt
   */
  void setSocketOptions(int level, int name, void *value, socklen_t);// throw(SystemException);

  /* Get socket options.
   * @params same to ::getsockopt
   */
  void getSocketOptions(int level, int name, void *value, socklen_t&);// throw(SystemException);

  /* Disable tcp delay
   * @param enable disable tcp delay
   */
  void setTcpNoDelay(bool enable);// throw(SystemException);

  /* Exclude address usage.
   * @throws SystemException on fail.
   */
  void setExclusiveAddrUse();// throw(SystemException);

  /* Close Tcp connection
   */
  void close();// throw(SystemException);

private:
  /* Initialize socket with another
   * @param socket socket created outside
   */
  Ipv4Socket(int socket);

  int  m_socket;

  Ipv4Endpoint *m_endpoint;
};

#endif // IPV4SOCKET_H
