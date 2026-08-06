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
	bool in_quotes = false, in_var = false, in_func = false;
	char word[1024], line[1024];
	i32 idx = 0, len = 0;
	for(int i = 0; i < a->filesize; i++)
	{
		if(a->content[i - 1] == '/' || a->content[i] == '/')
		{
			while(a->content[i++] != '\n');
			i--;
			continue;
		}

		if(a->content[i] == '\t' || a->content[i] == '\r' || a->content[i] == '\n')
		{
			word[0] = '\0';
			idx = 0;
			continue;
		}

		/* Tokens */
		if(find_type(word) != _DT_NULL && a->content[i + 1] == ';') {
			fsl_warning("expected function or variable name!")
			while(a->content[i++] != '\n'); // create err here then skip line
			i--;
			continue;
		} else if(a->content[i] == ' ')
		{				

			word[idx++] = '\0';
			_Datatype type;
			if((type = find_type(word)) != _DT_NULL)
			{

				char arg[1024];
				int arg_len = 0, n = i+ 1;
				while(a->content[n] != ' ' && a->content[n] != '\n' && a->content[n] != '\r' && a->content[n] != '[' && a->content[n] != '(' && a->content[n] != ';' && a->content[n] != '\t')
					arg[arg_len++] = a->content[n++];

				arg[arg_len] = '\0';
				_printf("Symbol Name: '%s'\n", arg);
				arg[0] = '\0';

				if(str_cmp(word, (string)__DATA_TYPES_INFO__[_DT_struct][1]))
				{
					println("Struct Found\n"); // Create array
					while(a->content[n++] != '}');

					i = n;
				} else if(a->content[n] == '[' || a->content[n] == ';') {
					println("Variable Found\n"); // Get the fixed size
				} else if(a->content[n] == '(')
				{
					println("Function Found\n"); // Parse Function
					process_function(a->content, &n);
					i = n;
					printc(a->content[i]);
				} else {
					fsl_warning("expected function or variable name!");
				}
			}

			word[0] = '\0';
			idx = 0;
			continue;
		}

		if(mem_cmp(a->content + i, "asm", 3)) {
			i += 3;

			if(mem_cmp(a->content + i, "(\"", 2)) {
				in_quotes = true;
			}

			char asm_[1024];
			int asm_len = 0, n = i + 2;
			while(a->content[n] != '"')
				asm_[asm_len++] = a->content[n++];

			asm_[asm_len++] = '\0';
			_printf("ASM: %s\n", asm_);

			if(a->content[n] == ')');
			i = n;

			continue;
		}

		if((in_quotes && a->content[i] == '"') || is_ascii_alpha(a->content[i]) || is_ascii_digit(a->content[i]))
		{
			if(idx >= 1023) { /* Doubt, It'll Reach Here */
				word[0] = '\0';
				idx = 0;
			}

			word[idx++] = a->content[i];
		}

		// (*a->content)++;
	}

	pfree_array((array)a->lines);
	_pfree(a->filename);
	_pfree(a->content);
}

/* Parse Instruction Sets */
public ptr parse_instruction(_asmblr *a, string line)
{
	char instru[15];
	if(checknget_instruction(line, instru) == -1) {
		/* TODO; Set an error here, Invalid code */
		return NULL;
	}

	int operand_count = 0;
	sArr operands = split_string(line, ' ', &operand_count);
	if(operand_count == 0 || !operands) {
		printi(operand_count), println(NULL);
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
			return (i8 [])_SYSCALL;
			break;
		case _int:
		return (i8 [])_INT_0x80;
			break;
		case ret:
			break;
	}
}