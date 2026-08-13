#include "types.h"

public bool process_struct(struct_t st, string st_line, int *pos)
{
	if(!st || !st_line)
		return false;

	char word[1024];
	i32 in_struct = 0, len = 0, words = 0;
	for(; st_line[*pos] != '\0'; (*pos)++)
	{
		if(st_line[*pos] == '{') {
			in_struct = 1;
		}

		if(st_line[*pos] == '}') {
			in_struct = 0;
			break;
		}

		if(!in_struct)
			continue;

		if(st_line[*pos] == ' ')
		{
			word[len] = '\0';

			_Datatype t;
			if((t = find_type(word)) != _DT_NULL)
			{
				_printf("Struct Member: '%s'\n", word);
			}

            if(words % 2 == 0)
            {
                char ch = get_next_symbol_pos_only(st_line, pos);
				
				printc(ch);
				if(ch == ';') {
					skip_line(st_line, pos);
					continue;
				}

				/* TODO; fix */
                if(ch == '[') {
                    println("FUCKED");
                    var_t v = allocate(0, sizeof(_variable));
					int n = process_variable(v, st_line, pos);
                    _printf("OUTPUT: %d\n", (ptr)&n);
				}
            }

			word[0] = '\0';
			len = 0;
            words++;
			skip_line(st_line, pos);
			continue;
		}

		if(st_line[*pos] == '\n')
		{
			word[0] = '\0';
			len = 0;
			continue;
		}

		if(validate_whitespace(st_line[*pos]))
			continue;

		word[len++] = st_line[*pos];
	}
	return false;
}
