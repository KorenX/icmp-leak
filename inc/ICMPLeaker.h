#ifndef __ICMP_LEAKER_H__
#define __ICMP_LEAKER_H__

#include "ICMPSocket.h"
#include "IODataStream.h"

class ICMPLeaker
{
public:
    ICMPLeaker();
    bool Init();
    bool LeakData(IODataStream& leak_data_stream);

private:

    bool CreateResponse(IODataStream& leak_data_stream, ICMPMessage& request, ICMPMessage& response);
    bool m_init;
    ICMPSocket m_socket;
};

#endif // __ICMP_LEAKER_H__