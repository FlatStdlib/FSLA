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

	ptr		**ast;
	i64		ast_count;
	u8		*opcode;
	i32		size;
	string  *buffers;
} _asmblr;

_asmblr init_assembler(string filename);
public fn parse_file(_asmblr *a, bool struct_only, int cline);

#endif
