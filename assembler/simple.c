#include <fsl.h>

/* 64bit Size in Bytes */
#define a_CHAR_SZ 1
#define a_INT_SZ 4
#define a_BOOL_SZ 4
#define a_FLOAT_SZ 4
#define a_DOUBLE_SZ 8

typedef enum {
	a_BYTE 		= 1,
	a_SHORT 	= 2,
	a_INT 		= 3,
	a_BOOL 		= 4,
	a_FLOAT 	= 5,
	a_DOUBLE 	= 6
} data_t;

#define DATA_T_COUNT 6

void *DATA_TYPES[][2] = {
	{(ptr)a_BYTE, 	"i8"},
	{(ptr)a_SHORT,  "i16"},
	{(ptr)a_INT, 	"i32"},
	{(ptr)a_BOOL, 	"i32"},
	{(ptr)a_FLOAT, 	"i64"},
	{(ptr)a_DOUBLE, "i64"},
	NULL
};

data_t find_type(string q)
{
	for(int i = 0; i < DATA_T_COUNT; i++)
	{
        int len = str_len((char *)((void **)DATA_TYPES[i])[1]);
		if(mem_cmp((char *)((void **)DATA_TYPES[i])[1], q, len))
        {
			return (data_t)DATA_TYPES[i][0];
        }
	}

	return -1;
}

string find_stype(data_t q)
{
	for(int i = 0; i < DATA_T_COUNT; i++)
	{
		if(*(int *)DATA_TYPES[i][0] == q)
			return (string)DATA_TYPES[i][1];
	}

	return NULL;
}

struct parser_settings
{
	bool in_single_quote;
	bool in_double_quote;
	bool in_function;
	bool in_variable;
};

typedef struct {
    data_t  type;
    string  name;
    int     is_int;
} var;

typedef struct
{
    data_t  type;
    string  name;
    int     parameters;
} fnc;

var variable[25] = {0};
int var_count = 0;

fnc fncs[25] = {0};
int fnc_count = 0;

char *ERRORS[25] = {0};
int ERR_COUNT = 0;

bool validate_var(string line, int line_n)
{
    if(!line)
        return false;

    int argc = 0;
    sArr args = split_string(line, ' ', &argc);
    if(!argc || !args || argc < 2)
    {
        _sprintf(_OUTPUT_, "err: #%d, Invalid declaration, Missing variable name!", (void *[]){(ptr)&line_n});
        ERRORS[ERR_COUNT] = str_dup(_OUTPUT_);
        ERR_COUNT++;
        return false;
    }

    data_t type = find_type(args[0]);
    string name = str_dup(args[1]);
}

bool validate_func(string line, int line_n)
{
    if(!line)
        return false;

    int argc = 0;
    sArr args = split_string(line, ' ', &argc);
    if(!argc || !args || argc < 2)
    {
        _sprintf(_OUTPUT_, "err: #%d, Invalid declaration, Missing function name!", (void *[]){(ptr)&line_n});
        ERRORS[ERR_COUNT] = str_dup(_OUTPUT_);
        ERR_COUNT++;
        return false;
    }

    data_t type = find_type(args[0]);
    string name = str_dup(args[1]);

    if(str_endswith(name, "()"))
    {
        /* Parameters can be ignored if there isnt any */
        name[__get_size__(name) - 3] = '\0';
        name[__get_size__(name) - 2] = '\0';
    }

    fnc fn;
    memzero(&fn, sizeof(fnc));
    fn.type = type;
    fn.name = name;

    mem_cpy(&fncs[fnc_count], &fn, sizeof(fn));
    fnc_count++;
    pfree_array((array)args);
}

int entry(int argc, string argv[])
{
    int check = find_type("i8");
    _printf("Check: %d\n", &check);

	/* Simple NASM syntax Assembler */
	if(argc < 2)
	{
		_printf("Invalid arguments provided!\nUsage %s <file>\n", argv[0]);
		return 1;
	}

	fd_t fd = open_file(argv[1], 0, 0);
	if(!fd)
		fsl_panic("Unable to open file!");

	int sz 			= file_content_size(fd);
	string buffer 	= allocate(0, sz + 1);
	int bytes 		= file_read(fd, buffer, sz);
	if(bytes <= 0)
		fsl_panic("Read err");

	int line_count 	= 0;
	sArr lines 		= split_lines(buffer, &line_count);

	struct parser_settings s = {false};
	for(int i = 0; i < line_count; i++)
	{
		if(!lines[i])
			break;

		if(is_empty(lines[i])) continue;

		int arg_c = 0;
		sArr args = split_string(lines[i], ' ', &arg_c);
		if(!arg_c || !args)
			continue;

		_printf("[%d]: %s\n", (ptr)&i, lines[i]);
        int chk = find_type(args[0]);
		if(chk > -1)
		{
			_printf("Function found: %s\n", args[1]);
			s.in_function = true;
            validate_func(lines[i], i);
		}

		pfree(args, 1);
		arg_c = 0;
	}

    if(ERR_COUNT > 0)
    {
        for(int i = 0; i < ERR_COUNT; i++)
            println(ERRORS[i]);
    }

    if(var_count > 0)
    {
        for(int i = 0; i < var_count; i++)
            _printf("Variable Noted: %s\n", variable[i].name);
    }

    if(fnc_count)
    {
        for(int i = 0; i < fnc_count; i++)
            _printf("Function Noted: %s\n", fncs[i].name);
    }

	return 0;
}