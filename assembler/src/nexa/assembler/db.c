#include "opcode.h"

struct _reg _REGISTERS[] = {
    { eax, "eax", "rax" },
    { ebx, "ebx", "rbx" },
    { ecx, "ecx", "rcx" },
    { edx, "edx", "rdx" },
    { ebp, "ebp", "rbp" },
    { esp, "esp", "rsp" },
    { edi, "edi", "rdi" },
    { esi, "esi", "rsi" }
};

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

/*
    INSTRUCTION | IDENIFIER | OPERANDS | Byte Gen Handler
*/
struct instruction_set INSTRUCTION_SETS[] = {
    {inc,       "inc",      1},
    {jmp,       "jmp",      1},
    {xor,       "xor",      2},
    {mov,       "mov",      2, mov_gen},
    {lea,       "lea",      2, lea_gen},
    {_int,      "int",      1},
    {syscall,   "syscall",  0},
    {ret,       "ret",      0}
};

public instruction_t checknget_instruction(string q, string dest)
{
	if(!q)
		return -1;

	for(int i = 0; q[i] != '\0'; i++)
	{
		if(q[i] == ' ')
			return i;

		dest[i] = q[i];
	}

	return -1;
}

public i64 get_instruction_info(string instruction)
{
	if(!instruction)
		return -1;

	for(int i = 0; i < TOTAL_INSTRUCTIONS; i++)
	{
		if(str_cmp(INSTRUCTION_SETS[i].id, instruction)) {
			return i;
        }
	}

	return -1;
}


const u8 NULL_TERMINATOR = '\0';
const u8 E_O_C[] = {0xFF, 0x00, 0xFF};
const u8 BLACKSPACE = 0xFF;