#include "src/init.h"

public int entry()
{
    int *g = syscall_gen();
    for(int i = 0; i < 2; i++)
        printi(g[i]), println(NULL);
    return 0;
}