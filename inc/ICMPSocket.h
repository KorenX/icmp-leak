#ifndef __ICMP_SOCKET_H__
#define __ICMP_SOCKET_H__

#include "ICMPMessage.h"

class ICMPSocket
{
public:
    ICMPSocket();
    bool Init();
    bool Receive(ICMPMessage& o_message);
    bool Send(const ICMPMessage& message);

private:
    int m_init;
    int m_socket_fd;
    struct sockaddr m_last_sender;
    socklen_t m_last_sender_size;

    static constexpr size_t IPHEADER_SIZE = 20;
};

#endif // __ICMP_SOCKET_H__
