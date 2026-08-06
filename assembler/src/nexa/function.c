#include <fsl.h>
#include "types.h"

void process_body(string fnc, int *pos);

_function *process_function(string fnc, int *pos)
{
    char types[6][1024];
    int idx = 0, len = 0, in_fnc = 0, in_quotes = 0, in_arg_field = 0;
    for(; fnc[*pos] != '\0'; (*pos)++)
    {
        if(fnc[*pos] == '(') {
            in_arg_field = 1;
            continue;
        }

        if(fnc[*pos] == ')') {
            types[idx][len] = '\0';
            idx++;
            in_arg_field = 0;
            (*pos)+= 2;
            break;
        }

        if(!in_arg_field && fnc[*pos] == ')') {
            fsl_panic("missing an opening bracket!");
        }

        if(fnc[*pos] == ',')
        {
		    types[idx][len] = '\0';
            idx++;
            len = 0;
        }

        if(is_ascii_alpha(fnc[*pos]) || is_ascii_digit(fnc[*pos]))
		{
			if(len >= 1023) { /* Doubt, It'll Reach Here */
				types[idx][0] = '\0';
				len = 0;
                idx++;
			}

			types[idx][len++] = fnc[*pos];
		}
    }


    for(int i = 0; i < idx; i++)
    {
        println(types[i]);
	    types[0][0] = '\0';
    }
    
    process_body(fnc, pos);
}

void process_body(string fnc, int *pos)
{
    printc(fnc[*pos]), println(NULL);
    char word[1024];
    int idx = 0, in_fnc = 0, in_quotes = 0, in_arg_field = 0;
    for(; fnc[*pos] != '\0'; (*pos)++)
    {
        if(fnc[*pos] == '{') {
            in_fnc = 1;
        }

        if(fnc[*pos] == '}') {
            in_fnc = 0;
            (*pos)++;
            break;
        }

        if(!in_fnc && fnc[*pos] == '}') {
            fsl_panic("missing an opening bracket!");
            break;
        }
        
        if(fnc[*pos] == '\t' || fnc[*pos] == '\r' || fnc[*pos] == '\n')
		{
			word[0] = '\0';
			idx = 0;
			continue;
		}

        /* Function Call */
        if(mem_cmp(fnc + *pos, "asm", 3)) {
			*pos += 3;

			if(mem_cmp(fnc + *pos, "(\"", 2)) {
				in_quotes = true;
			}

			char asm_[1024];
			int asm_len = 0, n = *pos + 2;
			while(fnc[n] != '"')
				asm_[asm_len++] = fnc[n++];

			asm_[asm_len++] = '\0';
			_printf("ASM: %s\n", asm_);

			if(fnc[n] == ')');
			*pos = n;

			continue;
		}

        if((in_quotes && fnc[*pos] == '"') || is_ascii_alpha(fnc[*pos]) || is_ascii_digit(fnc[*pos]))
		{
			if(idx >= 1023) { /* Doubt, It'll Reach Here */
				word[0] = '\0';
				idx = 0;
			}

			word[idx++] = fnc[*pos];
		}
    }
}