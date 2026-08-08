#include "opcode.h"

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