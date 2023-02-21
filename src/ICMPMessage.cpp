#include "ICMPMessage.h"
#include <stdio.h>
#include <string.h>

ICMPMessage::ICMPMessage() : code(0), type(0), checksum(0), content(0), payload{0}
{

}

bool ICMPMessage::Deserialize(void* buffer, size_t size)
{
    size_t header_size = reinterpret_cast<size_t>(&payload) - reinterpret_cast<size_t>(&code);
    if (size < header_size)
    {
        printf("not enough data passed\r\n");
        return false;
    }


    size_t payload_copy_size = (size - header_size > MAX_PAYLOAD ? MAX_PAYLOAD : size - header_size);

    memcpy(&code, buffer, header_size + payload_copy_size);
    printf("%x\n", code);
    printf("%x\n", type);
    printf("%x\n", checksum);
    printf("%x\n", content);
    return true;
}

void ICMPMessage::CalculateChecksum()
{
    uint16_t chksum = 0;
    checksum = 0;

    for (size_t i = 0; i < sizeof(ICMPMessage); i+=2)
    {
        chksum += ((uint8_t*)this)[i] << 8;
        chksum += ((uint8_t*)this)[i+1];
    }

    checksum = chksum;
}
