#include "init.h"

/* Convert a register in string to reg_t  */
mov reg_to_type(string reg)
{
    for(int i = 0; i < REG_COUNT; i++)
    {
        if(str_cmp(REGISTERS[i].x86, reg) || str_cmp(REGISTERS[i].x64, reg))
            return REGISTERS[i].opcode;
    }

    return -1;
}