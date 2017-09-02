#include "winsockinitializer.h"
#include <WinSock2.h>

void WinSockInitializer::startup()
{
  WSADATA wsaData;
  ::WSAStartup(MAKEWORD(2, 2), &wsaData);
}


void WinSockInitializer::cleanup()
{
  ::WSACleanup();
}