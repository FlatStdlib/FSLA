#include "init.h"

public u8 *syscall_gen()
{
    static u8 n[] = {0x0F, 0x05};
    return n;
}

public u8 *int_0x80_gen()
{
    static u8 n[] = {0xCD, 0x80};
    return n;
}

public u8 *mov_gen(u8 reg)
{
    /* register & 4 bit representation */
    static u8 mov32[10] = {0};

    /* register & 8 bit representation */
    static u8 mov64[5] = {0x48};

    return NULL;
}

public u8 *lea_gen(u8 reg)
{
    static u8 lea32[] = {0};
    
    static u8 lea64[] = {0x48};
    return NULL;
}