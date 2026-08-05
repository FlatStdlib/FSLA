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

/*
	Validate Integer

	returns the exact bytes for imm64 and can be used as and for imm32
*/
public u64 validate_integer(string val)
{
	if(!val)
		return false;

	int n = _str_len(val);
	if(n == 0)
		return false;

	u64 result = 0;
	if(n >= 2 && val[0] == '0' && val[1] == 'x')
	{
        for(int i = 2; i < n; i++)
        {
            u8 c = hex_value(val[i]);
            if(c == 0xff)
                return -1;

            result = (result << 4) | c;
        }

        return result;
	}

	if(is_number(val))
	{
        for(int i = 0; i < n; i++)
        {
			if(val[i] < '0' || val[i] > '9')
				return -1;

			int c = val[i] - '0';
			result = (result * 10) + c;
        }

        return result;
	}

	return false;
}

u8 hex_value(char c)
{
    if(c >= '0' && c <= '9')
        return c - '0';

    if(c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    if(c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0xff;
}
