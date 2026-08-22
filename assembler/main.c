#include "src/init.h"

public int entry()
{
    // toggle_debug_mode();
    _asmblr a = init_assembler("lul.n");
    parse_file(&a, 0, 0);

    for(int i = 0; i < a.ast_count; i++)
    {
        if(!((var_t *)a.ast)[i])
            continue;

        var_t n = ((var_t *)a.ast)[i];
        if(n->feature == n_variable)
        {
            _printf("[%d]: Type: %d - %s | Variable: %s | Size: %d\n",  &i, &n->type, get_type_rstring(n->type), n->name, (ptr)&n->length);
        } else if(n->feature == n_function)
        {
            _printf("[%d]: Return Type: %d | Function: %s | Size: %d\n", &i, (ptr)&n->type, n->name, &((fn_t)n)->count);
        } else {
            _printf("-> [%d]: %s\n", (ptr)&i, n->name);
        }
    }

    return 0;
}
