#include "init.h"

public int *syscall_gen()
{
    static int n[] = (int []){0x0F, 0x05};
    return n;
}