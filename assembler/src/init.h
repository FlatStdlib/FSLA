#include <fsl.h>

#include "nexa/types.h"

#ifndef __NEXA_LANG__

typedef struct
{
	fd_t 	file;
	string 	filename;
	int 	filesize;
    sArr    lines;
    i64     line_count;
	arch_t	arch;
	string	content;

	array 	ast;
	u8		*opcode;
	i32		size;
	string  *buffers;
} _asmblr;

_asmblr init_assembler(string filename);
public fn parse_file(_asmblr *a);

void skip_line(string buffer, int *pos);
bool validate_whitespace(char c);
i8 get_next_token(string buffer, int pos);
char get_next_symbol_only(string buffer, int pos);
char get_next_token_only(string buffer, int pos);

#endif
