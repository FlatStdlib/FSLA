#include "init.h"

public _asmblr init_assembler(string filename)
{
	_asmblr a;
	memzero(&a, sizeof(_asmblr));

	a.file = open_file(filename, 0, 0);
	if(!a.file)
		return (_asmblr){0};

	a.filename = str_dup(filename);
	if((a.filesize = file_content_size(a.file)) <= 0)
		fsl_panic("Unable to read file...!");

	a.content = allocate(0, a.filesize + 1);
	int bytes = file_read(a.file, a.content, a.filesize);
	if(bytes <= 0)
		fsl_panic("Unable to read file...!");

	file_close(a.file);
	return a;
}


/* For The Language Parser */
public fn parse_file(_asmblr *a)
{
	
}

/* Parse Instruction Sets */
public fn parse_instruction(_asmblr *a, string line)
{
	int args = 0;
	if((args = find_char(line, ' ')) > -1)
	{
		i64 instru = get_instruction_info(a, line);
		return;
	}

	i64 instru = get_instruction_info(a, line);
	_iset i = INSTRUCTION_SETS[instru];
	switch(i->in)
	{
		case xor:
		case mov:
		case jmp:
	}
}