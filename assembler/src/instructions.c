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
        - Integer			= 3
        - Offset Pointer	= 0x00000000
        - Variable
*/
public u8 *mov_gen(u8 reg, string q, arch_t arch)
{
	static u8 _mov[10] = {0};

	if(arch == x86)
	{
		_mov[0] = reg;
		if(is_number(q)) {
			_mov[1] = q[0] - '0';
		}
	} else if(arch == x86_64) {
        _mov[0] = 0x48;
        _mov[1] = reg;
		if(is_number(q)) {
			_mov[2] = q[0] - '0';
		}
	} else {
		fsl_panic("Invalid cpu architecture target for the lea instruction set");
	}

    return NULL;
}

public u8 *lea_gen(u8 reg, string q, arch_t arch)
{
	static u8 _lea[10] = {0};

	if(arch == x86)
	{
		_lea[0] = reg;
		if(is_number(q)) {
			_lea[1] = q[0] - '0';
		}
	} else if(arch == x86_64) {
        _lea[0] = 0x48;
        _lea[1] = reg;
		if(is_number(q)) {
			_lea[2] = q[0] - '0';
		}
	} else {
		fsl_panic("Invalid cpu architecture target for the lea instruction set");
	}
    return NULL;
}
