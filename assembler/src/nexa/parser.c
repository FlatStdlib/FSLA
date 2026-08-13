#include "types.h"

public void skip_line(string buffer, int *pos)
{
	while(buffer[*pos] != '\n')
	{
		(*pos)++;
	}
}

public void skip_all_whitespaces(string buffer, int *pos)
{
	while(validate_whitespace(buffer[*pos]) != false || buffer[*pos] != ' ')
	{
		(*pos)++;
	}
}

public void skip_whitespaces(string buffer, int *pos)
{
	while(validate_whitespace(buffer[*pos]) != false)
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
char get_next_symbol_pos_only(string buffer, int *pos)
{
	for(; buffer[*pos] != '\0'; (*pos)++)
	{
		/* Only Skip Whitespaces*/
		if(buffer[*pos] == ' ' || buffer[*pos] == '\t' || buffer[*pos] == '\r' || buffer[*pos] == '\n') {
			continue;
		}

		if(is_ascii_alpha(buffer[*pos]) || is_ascii_digit(buffer[*pos])) {
			return -1;
		}
			
		if(buffer[*pos] > 0 && buffer[*pos] < 127) {
			return buffer[*pos];
		}
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
