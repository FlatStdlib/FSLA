#pragma once

#include <fsl.h>

#include "assembler/opcode.h"

extern bool __NDEBUG__;

#ifndef __NEXA_TYPES__

typedef enum
{
	n_variable,
	n_function,
	n_struct
} nexa_features;

typedef enum {
    _DT_NULL = -1,
    _DT_void,
    _DT_u8,
    _DT_i8,
    _DT_u16,
    _DT_i16,
    _DT_u32,
    _DT_i32,
    _DT_u64,
    _DT_i64,
    _DT_f32,
    _DT_f64,
    _DT_ptr,
    _DT_skiddy_baloo,
    _DT_struct
} _Datatype;

typedef struct __attribute__((packed)) {
    nexa_features   feature;
    bool            is_const;
    _Datatype       type;
    string          name;
    string          value;
    i64 		    size;
    i64				length;
    bool            fixed_size;

    u8              *opcode;
    i64             count;
} _variable;

typedef struct {
	nexa_features	feature;
	bool			is_const;
	_variable		**members;
	string			name;
	i64 			length;

	u8				*opcode;
	i64				count;
} _struct;

typedef struct __attribute__((packed)) {
    nexa_features   feature;
    bool            is_const;
    _Datatype       type;
    string          name;
    array           arg_types;
    i32             arg_count;
    string          *body;

    u8              *opcode;
    i64             count;
} _function;

typedef _function *fn_t;
typedef _variable *var_t;
typedef _struct *struct_t;

#ifndef __TYPE_SIZE__
    #define __DT_void   0

    #define __DT_u8     1
    #define __DT_u16    2
    #define __DT_u32    4
    #define __DT_u64    8

    #define __DT_i8     1
    #define __DT_i16    2
    #define __DT_i32    4
    #define __DT_i64    8

    #define __DT_ptr    8
#endif

extern void *__DATA_TYPES_INFO__[][3];

/* types.c */
_Datatype find_type(string q);
int get_type_size(_Datatype t);

/* function.c */
public bool process_function(fn_t fnc, string fnc_line, int *pos);
public bool process_function_body(fn_t fnc, string fnc_line, int *pos);

/* variable.c */
public bool process_variable(var_t var, string var_line, int *pos);
public bool process_variable_value(var_t var, string var_line, int *pos);

/* struct.c */
public bool process_struct(struct_t st, string st_line, int *pos);

/* parser.c */
public void skip_all_whitespaces(string buffer, int *pos);
public void skip_whitespaces(string buffer, int *pos);
public void skip_line(string buffer, int *pos);
bool validate_whitespace(char c);
i8 get_next_token(string buffer, int pos);
char get_next_symbol_pos_only(string buffer, int *pos);
char get_next_symbol_only(string buffer, int pos);
char get_next_token_only(string buffer, int pos);

#endif
