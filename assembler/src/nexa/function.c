#include <fsl.h>
#include "types.h"

char get_next_symbol_only(string buffer, int pos);
public fn_t process_function(string fnc_line, int *pos)
{
    _function fnc;
    memzero(&fnc, sizeof(_function));

    char types[6][1024];
    types[0][0] = '\0';
    int idx = 0, len = 0, in_arg_field = 0;
    for(; fnc_line[*pos] != '\0'; (*pos)++)
    {
        if(fnc_line[*pos] == '(') {
            in_arg_field = 1;
            continue;
        }

        if(fnc_line[*pos] == ')') {
            if(types[0][0] != '\0') idx++;
            in_arg_field = 0;
            (*pos)+= 2;
            break;
        }

        if(!in_arg_field && fnc_line[*pos] == ')') {
            fsl_panic("missing an opening bracket!");
        }

        if(fnc_line[*pos] == '\t' || fnc_line[*pos] == '\r' || fnc_line[*pos] == '\n' || fnc_line[*pos] == ',')
            continue;

        if(fnc_line[*pos] == ' ')
        {
        	if(types[idx][0] == '\0') continue;
        	while(fnc_line[*pos] != ' ') (*pos)++;
		    types[idx][len++] = '\0';
            if(types[0][0] != '\0' && idx % 2 == 0 && find_type(types[idx]) == _DT_NULL) {
                _printf("Invalid data type for function argument: '%s'\n", types[idx]);
            }
            if(types[idx][0] != '\0') idx++;
            len = 0;
            continue;
        }

        if(is_ascii_alpha(fnc_line[*pos]) || is_ascii_digit(fnc_line[*pos]))
		{
			if(len >= 1023) { /* Doubt, It'll Reach Here */
				types[idx][0] = '\0';
				len = 0;
                idx++;
			}

			types[idx][len++] = fnc_line[*pos];
		}
    }

    for(int i = 0; i < idx; i++)
    {
        print("-> '"), print(types[i]), print("'\n");
	    types[0][0] = '\0';
    }

	_printf("Args: %d\n", (ptr)&idx);
    if(types[0][0] != '\0' && idx % 2)
        fsl_panic("Invalid function arguments\n");

	memzero(types, sizeof(types));
    process_function_body(&fnc, fnc_line, pos);
    return NULL;
}

public fn process_function_body(fn_t fnc, string fnc_line, int *pos)
{
    if(!fnc)
        return;

    // printc(fnc_line[*pos]), println(NULL);
    char word[1024];
    int idx = 0, in_fnc = 0, in_quotes = 0, in_arg_field = 0;
    for(; fnc_line[*pos] != '\0'; (*pos)++)
    {
        if(fnc_line[*pos] == '{') {
            in_fnc = 1;
        }

        if(fnc_line[*pos] == '}') {
            in_fnc = 0;
            (*pos)++;
            break;
        }

        if(!in_fnc && fnc_line[*pos] == '}') {
            fsl_panic("missing an opening bracket!");
            break;
        }
        
        if(fnc_line[*pos] == '\t' || fnc_line[*pos] == '\r' || fnc_line[*pos] == '\n')
		{
			word[0] = '\0';
			idx = 0;
			continue;
		}

        /* 
            TODO; implement find_symbol() and detect function call or memory modification
        */
        if(mem_cmp(fnc_line + *pos, "asm", 3)) {
			*pos += 3;

			if(mem_cmp(fnc_line + *pos, "(\"", 2)) {
				in_quotes = true;
			}

			char asm_[1024];
			int asm_len = 0, n = *pos + 2;
			while(fnc_line[n] != '"')
				asm_[asm_len++] = fnc_line[n++];

			asm_[asm_len++] = '\0';
			_printf("ASM: %s\n", asm_);
            u8 *opcode = parse_instruction(asm_, x86_64);
            char byte[3];
            byte_to_hex(opcode[0], byte);
            println(byte);
            byte_to_hex(opcode[1], byte);
            println(byte);

			if(fnc_line[n] == ')');
			*pos = n;

			continue;
		}

        if((in_quotes && fnc_line[*pos] == '"') || is_ascii_alpha(fnc_line[*pos]) || is_ascii_digit(fnc_line[*pos]))
		{
			if(idx >= 1023) { /* Doubt, It'll Reach Here */
				word[0] = '\0';
				idx = 0;
			}

			word[idx++] = fnc_line[*pos];
		}
    }
}
