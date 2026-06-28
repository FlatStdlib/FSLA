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
public ptr parse_instruction(_asmblr *a, string line)
{
	char instru[15];
	if(checknget_instruction(line, instru) == -1) {
		/* TODO; Set an error here, Invalid code */
		return NULL;
	}

	i64 pos = get_instruction_info(a, instru);
	_iset i = INSTRUCTION_SETS[pos];
	switch(i.in)
	{
		case inc:
			break;
		case xor:
			break;
		case mov:
			break;
		case jmp:
			break;
		case syscall:
			// return (ptr){0x0F, 0x05};
			break;
		case int_0x80:
			break;
		case ret:
			break;
	}
}
