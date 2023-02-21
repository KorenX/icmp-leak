#ifndef __FAKE_DATA_STREAM_H__
#define __FAKE_DATA_STREAM_H__

#include "IODataStream.h"
#include <memory.h>

class FakeDataStream : public IODataStream
{
public:
    bool Read(uint8_t* buffer, size_t buffer_size) override;
};

bool FakeDataStream::Read(uint8_t* buffer, size_t buffer_size)
{
    memset(buffer, 0, buffer_size);
    const char* fake_data = "Faker";
    memcpy(buffer, fake_data, sizeof(fake_data));
    return true;
}

#endif // __FAKE_DATA_STREAM_H__
