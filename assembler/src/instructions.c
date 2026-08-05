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

/*
    Acceptable Value Usage:
        - Integer			= 0x3
        - Offset Pointer	= 0x00000000
*/
public u8 *mov_gen(reg_t reg, string q, arch_t arch)
{
	u8 _mov[10] = {0};

	if(arch == x86)
	{
		_mov[0] = reg;
		u64 u = validate_integer(q);
		if(!u)
			fsl_warning("Integer is 0!");

		_mov[1] = u & 0xff;
		_mov[2] = (u >> 8) & 0xff;
		_mov[3] = (u >> 16) & 0xff;
		_mov[4] = (u >> 24) & 0xff;

		return to_heap(_mov, 5);
	} else if(arch == x86_64) {
        _mov[0] = 0x48;
        _mov[1] = reg;
		u64 u = validate_integer(q);
		if(!u)
			fsl_warning("Integer is 0!");

		for(int i = 0; i < 8; i++)
			_mov[2+i] = (u >> (i * 8)) & 0xff;

		return to_heap(_mov, 10);
	} else {
		fsl_panic("Invalid cpu architecture target for the lea instruction set");
	}

    return NULL;
}

public u8 *lea_gen(reg_t reg, string q, arch_t arch)
{
	static u8 _lea[10] = {0};

	if(arch == x86)
	{
		_lea[0] = reg;
		u64 u = validate_integer(q);
		if(!u)
			fsl_warning("Integer is 0!");

		_lea[1] = u & 0xff;
		_lea[2] = (u >> 8) & 0xff;
		_lea[3] = (u >> 16) & 0xff;
		_lea[4] = (u >> 24) & 0xff;

		return to_heap(_lea, 5);
	} else if(arch == x86_64) {
        _lea[0] = 0x48;
        _lea[1] = reg;
		u64 u = validate_integer(q);
		if(!u)
			fsl_warning("Integer is 0!");

		for(int i = 0; i < 8; i++)
			_lea[2+i] = (u >> (i * 8)) & 0xff;

		return to_heap(_lea, 10);
	} else {
		fsl_panic("Invalid cpu architecture target for the lea instruction set");
	}

    return NULL;
}
