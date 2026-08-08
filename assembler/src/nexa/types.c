#include "types.h"

#define __TOTAL_DATA_TYPES 13
void *__DATA_TYPES_INFO__[][2] =
{
    {(void *)_DT_void,      "void"},
    {(void *)_DT_u8,        "u8"},
    {(void *)_DT_i8,        "i8"},
    {(void *)_DT_u16,       "u16"},
    {(void *)_DT_i16,       "i16"},
    {(void *)_DT_u32,       "u32"},
    {(void *)_DT_i32,       "i32"},
    {(void *)_DT_u64,       "u64"},
    {(void *)_DT_i64,       "i64"},
    {(void *)_DT_f32,       "f32"},
    {(void *)_DT_f64,       "f64"},
    {(void *)_DT_ptr,       "ptr"},
    {(void *)_DT_struct,    "struct"},
    NULL
};

_Datatype find_type(string q)
{
    for(int i = 0; i < __TOTAL_DATA_TYPES; i++)
    {
        if(str_cmp(__DATA_TYPES_INFO__[i][1], q))
            return (_Datatype)__DATA_TYPES_INFO__[i][0];
    }

    return _DT_NULL;
}
