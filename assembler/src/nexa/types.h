#ifndef __NEXA_TYPES__

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
    _DT_struct
} _Datatype;

typedef struct {
    bool        is_const;
    _Datatype   type;
    string      name;
    string      value;
} _variable;

typedef struct {
    bool        is_const;
    _Datatype   type;
    string      name;
    _variable   **arg_types;
    i32         arg_count;
    string      *body;

    u8          *body_opcode;
    i64         opcode;
} _function;

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

extern void *__DATA_TYPES_INFO__[][2];

/* types.c */
_Datatype find_type(string q);

/* function.c */
_function *process_function(string fnc, int *pos);

#endif
