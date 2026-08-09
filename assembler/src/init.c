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
	a.ast = init_array();
	return a;
}


/* For The Language Parser */
public fn parse_file(_asmblr *a)
{
	bool in_quotes = false, in_var = false, in_func = false, ignore = false;
	char word[1024], line[1024];
	i32 idx = 0, len = 0;
	for(int i = 0; i < a->filesize; i++)
	{
		if(a->content[i] == '/' && a->content[i + 1] == '/') {
			while(a->content[i++] != '\n');
			i--;
			continue;
		} else if(a->content[i] == '/' && a->content[i + 1] == '*') {
			ignore = true;
			continue;
		} else if(ignore && a->content[i] == '*' && a->content[i + 1] == '/') {
			ignore = false;
			continue;
		}

		/* Ignore comments formatted like this */
		if(ignore) continue;

		if(validate_whitespace(a->content[i]))
		{
			word[0] = '\0';
			idx = 0;
			continue;
		}

		/* Tokens */
		if(a->content[i] == ' ')
		{

			word[idx++] = '\0';
			_Datatype type;
			if((type = find_type(word)) != _DT_NULL)
			{

				char symbol[1024]; /* Symbol Name*/
				int arg_len = 0, n = i + 1;
				while(a->content[n] != ' ' && a->content[n] != '\n' && a->content[n] != '\r' && a->content[n] != '{' && a->content[n] != '[' && a->content[n] != '(' && a->content[n] != ';' && a->content[n] != '\t')
					symbol[arg_len++] = a->content[n++];

				symbol[arg_len] = '\0';
				print("Symbol Name: '"), print(symbol), print("'\n");
				symbol[0] = '\0';

				if(str_cmp(word, (string)(__DATA_TYPES_INFO__[_DT_struct][1])))
				{
					println("Struct Found\n"); // Create array
					while(a->content[n++] != '}');

					i = n;
				// } else if(a->content[n] == '[' || a->content[n] == ';') {
				} else if(get_next_symbol_only(a->content, n) == '[' || get_next_symbol_only(a->content, n) == ';') {
					println("Variable Found\n"); // Get the fixed size
				} else if(get_next_symbol_only(a->content, n) == '(')
				{
					println("Function Found\n"); // Parse Function
					_function fnc;
    				memzero(&fnc, sizeof(_function));
					fnc.type = type;
					fnc.name = str_dup(symbol);
					process_function(&fnc, a->content, &n);
					i = n;
				} else {
					fsl_warning("expected function or variable name!");
				}
			}

			word[0] = '\0';
			idx = 0;
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

void skip_line(string buffer, int *pos)
{
	while(buffer[*pos] != '\n')
	{
		(*pos)++;
	}
}

bool validate_whitespace(char c)
{
	return (c == '\t' || c == '\r' || c == '\n');
}

i8 get_next_token(string buffer, int pos)
{
	for(int i = pos; buffer[i] != '\0'; i++)
	{
		/* Only Skip Whitespaces*/
		if(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\r' || buffer[i] == '\n')
			continue;

		return buffer[i];
	}

	return -1;
}

/* Returns the next ASCII symbol, non-alphabet or digit */
char get_next_symbol_only(string buffer, int pos)
{
	for(int i = pos; buffer[i] != '\0'; i++)
	{
		/* Only Skip Whitespaces*/
		if(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\r' || buffer[i] == '\n') {
			continue;
		}

		if(is_ascii_alpha(buffer[i]) || is_ascii_digit(buffer[i])) {
			return -1;
		}
			
		if(buffer[i] > 0 && buffer[i] < 127) {
			return buffer[i];
		}
	}

	return -1;
}

/* Returns the next ASCII character */
char get_next_token_only(string buffer, int pos)
{
	for(int i = pos; buffer[i] != '\0'; i++)
	{
		/* Only Skip Whitespaces*/
		if(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\r' || buffer[i] == '\n') {
			continue;
		}

		if(buffer[i] > 0 && buffer[i] < 127 && (is_ascii_alpha(buffer[i]) || is_ascii_digit(buffer[i]) || buffer[i] == '_'))
		{
			return buffer[i];
		}
	}

	return -1;
}
