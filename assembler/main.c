#include "src/init.h"

public int entry()
{
    u8 *g = int_0x80_gen();
    char byte[3];
    for(int i = 0; i < 2; i++) {
        byte_to_hex(g[i], byte);
        println(byte);
    }
    return 0;
}
