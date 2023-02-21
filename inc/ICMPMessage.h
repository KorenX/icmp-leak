#ifndef __ICMP_MESSAGE_H__
#define __ICMP_MESSAGE_H__

#include <sys/socket.h>
#include <netinet/ip_icmp.h>

#define MAX_PAYLOAD 56

#pragma pack(push, 1)
struct ICMPMessage
{
    uint8_t code;
    uint8_t type;
    uint16_t checksum;
    uint32_t content;
    uint8_t payload[MAX_PAYLOAD];

    ICMPMessage();
    bool Deserialize(void* buffer, size_t size);
    void CalculateChecksum();
};
#pragma pack(pop)

#endif // __ICMP_MESSAGE_H__