#ifndef __IO_DATA_STREAM_H__
#define __IO_DATA_STREAM_H__

#include <stdint.h>
#include <stddef.h>

class IODataStream
{
public:
    virtual bool Read(uint8_t* buffer, size_t buffer_size) = 0;
};

#endif // __IO_DATA_STREAM_H__