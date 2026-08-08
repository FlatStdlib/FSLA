#include "opcode.h"

static const u8 _SYSCALL[] = { 0x0F, 0x05 };
static const u8 _INT_0x80[] = { 0xCD, 0x80 };
static const u8 _RET[] = { 0xC3 };

/* Parse Instruction Sets */
public ptr parse_instruction(string line, arch_t arch)
{
	char instru[15] = {0};
	if(checknget_instruction(line, instru) == -1) {
		/* TODO; Set an error here, Invalid code */
		mem_cpy(instru, line, _str_len(line));
		// return NULL;
	}

	sArr operands = NULL;
	if(find_char(line, ' ') > -1)
	{
		int operand_count = 0;
		operands = split_string(line, ' ', &operand_count);
		if(operand_count < 2 || !operands) {
			printi(operand_count), println(NULL);
			return NULL;
		}

		operands[1][__get_size__(operands[1]) - 2] = '\0';
		println(operands[1]), println(NULL);
	}

	i64 pos = get_instruction_info(instru);
	if(pos == -1)
		fsl_panic("Invalid instruction...!");

	_iset i = INSTRUCTION_SETS[pos];
	switch(i.in)
	{
		case inc:
			break;
		case xor:
			break;
		case mov: 		
		println("HERE");
		return mov_gen(reg_to_type(operands[1]), operands[2], arch);
		case jmp:
			break;
		case syscall: 	return _SYSCALL;
		case _int: 		return _INT_0x80;
		case ret: 		return _RET;
	}
}

/*
    Acceptable Value Usage:
        - Integer			= 0x3
        - Offset Pointer	= 0x00000000
*/
public u8 *mov_gen(reg_t reg, string q, arch_t arch)
{
	println("HERE");
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