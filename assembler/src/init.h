#include <fsl.h>

#include "nexa/types.h"
#include "nexa/assembler/opcode.h"

#ifndef __FSL_ASM__


typedef struct
{
	fd_t 	file;
	string 	filename;
	int 	filesize;
    sArr    lines;
    i64     line_count;
	arch_t	arch;
	string	content;

	u8		*opcode;
	i32		size;
	string  *buffers;
} _asmblr;

_asmblr init_assembler(string filename);
public fn parse_file(_asmblr *a);
public ptr parse_instruction(_asmblr *a, string line);
public i64 get_instruction_info(_asmblr *a, string instruction);

public i64 get_instruction_info(_asmblr *a, string instruction);
reg_t reg_to_type(string reg);
public instruction_t checknget_instruction(string q, string dest);

public u8 *mov_gen(reg_t reg, string q, arch_t arch);
public u8 *lea_gen(reg_t reg, string q, arch_t arch);
public u64 validate_integer(string val);
u8 hex_value(char c);

public u8 *syscall_gen();
public u8 *int_0x80_gen();
#endif
