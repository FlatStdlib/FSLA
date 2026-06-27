#include "init.h"

public i64 get_instruction_info(_asmblr *a, string instruction)
{
	if(!instruction)
		return (i64)NULL;

	for(int i = 0; i < TOTAL_INSTRUCTIONS; i++)
	{
		if(str_cmp(INSTRUCTION_SETS[i].id, instruction))
			return i;
	}

	return (i64)NULL;
}

/* Convert a register in string to reg_t  */
reg_t reg_to_type(string reg)
{
    for(int i = 0; i < REG_COUNT; i++)
    {
        if(str_cmp(_REGISTERS[i].x86, reg) || str_cmp(_REGISTERS[i].x64, reg))
            return _REGISTERS[i].opcode;
    }

    return -1;
}


