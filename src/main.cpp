#include "ICMPLeaker.h"
#include "FakeDataStream.h"
#include <stdio.h>

int main()
{
    ICMPLeaker leaker;
    FakeDataStream leak_data_file;

    bool ret = leaker.Init();
    if (!ret)
    {
        printf("trouble in heaven\r\n");
        return 1;
    }

    ret = leaker.LeakData(leak_data_file);
    if (!ret)
    {
        printf("trouble in heaven 2\r\n");
        return 1;
    }

    return 0;
}