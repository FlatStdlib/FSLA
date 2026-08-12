#include "types.h"

public bool process_variable(var_t var, string var_line, int *pos)
{
    char size[100];
    int len = 0, _operator = 0;

	if(var_line[*pos] == '[')
	{
	    for(; var_line[*pos] != '\0'; (*pos)++)
	    {
	        if(var_line[*pos] == '[') {
	        	_operator = 1;
	            continue;
	        }

	        if(var_line[*pos] == ']') {
	        	_operator = 0;
	            (*pos)+= 2;
	            break;
	        }

	        if(!_operator && var_line[*pos] == ')') {
	            fsl_panic("missing an opening bracket!");
	        }

			if(validate_whitespace(var_line[*pos]))
				continue;

			if(is_ascii(var_line[*pos]) && !is_ascii_digit(var_line[*pos]))
				{ fsl_warning("invalid size"); break; }

			size[len++] = var_line[*pos];
	    }
	}

    if(len > 0)
    {
		size[len] = '\0';
		var->fixed_size = true;
		_printf("Fixed Size: %s\n", (ptr)&size);
		var->size = str_to_int((const string)size);
    } else {
    	var->size = get_type_size(var->type);
    	_printf("Type Size: %d\n", (ptr)&var->size);
    }

	skip_whitespaces(var_line, pos);

	char ch = get_next_symbol_only(var_line, *pos);
	if(ch == ';' || var_line[*pos] == ';') {
		return true;
	} else if(ch == '=')
	{
		(*pos)++;
		skip_all_whitespaces(var_line, pos);
		process_variable_value(var, var_line, pos);
	}

    return false;
}


public bool process_variable_value(var_t var, string var_line, int *pos)
{
	char value[1024];
	int len = 0;


	for(; var_line[*pos] != ';'; (*pos)++)
	{
		if(validate_whitespace(var_line[*pos]))
			continue;

		if(!is_ascii(var_line[*pos]))
			{ fsl_warning("invalid size"); break; }

		value[len++] = var_line[*pos];
	}

	str_strip(value);
	if(str_startswith(value, "\"") && str_startswith(value, "\""))
	{
		trim_char_idx(value, 0);
		value[len - 3] = '\0';

		if(!var->fixed_size)
		{
			for(int i = 0; i < 3; i++) len--;
			var->size = len;
			_printf("%s resized to %d\n", var->name, (ptr)&var->size);
		}
	}
	_printf("R: '%s'\n", value);
}
