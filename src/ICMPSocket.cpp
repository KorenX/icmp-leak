#include "ICMPSocket.h"
#include <stdio.h>
#include <errno.h>

ICMPSocket::ICMPSocket() : m_init(false) {}

bool ICMPSocket::Init()
{
    m_socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (m_socket_fd < 0)
    {
        printf("error creating socket: %d \r\n", errno);
        return false;
    }

    m_init = true;
    return true;
}

bool ICMPSocket::Receive(ICMPMessage& o_message)
{
    if (!m_init)
    {
        return false;
    }

    m_last_sender_size = sizeof(m_last_sender);
    int bytes_read = 0;
    uint8_t buff[sizeof(ICMPMessage) + IPHEADER_SIZE];

    bytes_read = recvfrom(m_socket_fd, buff, sizeof(buff), 0, &m_last_sender, &m_last_sender_size);
    if (bytes_read < 0)
    {
        printf("error receiving message: %d\r\n", errno);
        return false;
    }

    if (bytes_read < IPHEADER_SIZE)
    {
        printf("received non ip message\r\n");
        return false;
    }

    return o_message.Deserialize(buff + IPHEADER_SIZE, bytes_read - IPHEADER_SIZE);
}

bool ICMPSocket::Send(const ICMPMessage& message)
{
    if (!m_init)
    {
        return false;
    }

    int bytes_sent = sendto(m_socket_fd, &message, sizeof(ICMPMessage), 0, &m_last_sender, m_last_sender_size);
    if (bytes_sent < sizeof(ICMPMessage))
    {
        printf("error sending message: %d %d\r\n", bytes_sent, errno);
        return false;
    }

    return true; 
}
