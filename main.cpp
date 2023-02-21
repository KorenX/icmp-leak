#include <stdint.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MAX_PAYLOAD 24

#pragma pack(push, 1)
struct icmp_header
{
    uint8_t code;
    uint8_t type;
    uint16_t checksum;
    uint32_t content;
    uint8_t payload[MAX_PAYLOAD];
};
#pragma pack(pop)



int main()
{
    uint8_t buff[1024] = {0x00};
    int soc_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (soc_fd < 0)
    {
        printf("error creating socket: %d \r\n", errno);
        return (1);
    }

    struct sockaddr from;
    socklen_t fromlen = sizeof(from);
    int err = recvfrom(soc_fd, buff, sizeof(buff), 0, &from, &fromlen);
    if (soc_fd < 0)
    {
        printf("error receiving message: %d\r\n", err);
        return (1);
    }
    icmp_header req = {};
    memcpy(&req, &from, sizeof(req));

    for (size_t i = 0; i < err; i++)
    {
        printf("%u ", buff[i]);
    }
    printf("\r\n");

    const char* response = "hello";

    icmp_header resp = {};
    resp.type = 0;
    resp.code = 0;
    memcpy(resp.payload, response, sizeof(response));

    resp.content = req.content;

    uint16_t chksum = 0;

    for (size_t i = 0; i < sizeof(icmp_header); i+=2)
    {
        chksum += ((uint8_t*)&resp)[i] << 8;
        chksum += ((uint8_t*)&resp)[i+1];
    }

    resp.checksum = chksum;

    err = sendto(soc_fd, &resp, sizeof(resp), 0, &from, fromlen);

    return 0;
}