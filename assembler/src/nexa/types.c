#include "types.h"

#ifdef __NEXA_DEBUG__
	bool __NDEBUG__ = true;
#else
	bool __NDEBUG__ = false;
#endif

#define __TOTAL_DATA_TYPES 14
void *__DATA_TYPES_INFO__[][3] =
{
    {(void *)_DT_void,      "void",     (void *)0},
    {(void *)_DT_u8,        "u8",       (void *)1},
    {(void *)_DT_i8,        "i8",       (void *)1},
    {(void *)_DT_u16,       "u16",      (void *)2},
    {(void *)_DT_i16,       "i16",      (void *)2},
    {(void *)_DT_u32,       "u32",      (void *)4},
    {(void *)_DT_i32,       "i32",      (void *)4},
    {(void *)_DT_u64,       "u64",      (void *)8},
    {(void *)_DT_i64,       "i64",      (void *)8},
    {(void *)_DT_f32,       "f32",      (void *)4},
    {(void *)_DT_f64,       "f64",      (void *)8},
    {(void *)_DT_ptr,       "ptr",      (void *)8},
    {(void *)_DT_ptr,       "arc",      (void *)8},
    {(void *)_DT_struct,    "struct",   (void *)0},
    NULL
};

int get_type_size(_Datatype t)
{
	for(int i = 0; i < __TOTAL_DATA_TYPES; i++)
	{
		if((_Datatype)__DATA_TYPES_INFO__[i][0] == t)
			return (_Datatype)__DATA_TYPES_INFO__[i][2];
	}
}

_Datatype find_type(string q)
{
    for(int i = 0; i < __TOTAL_DATA_TYPES; i++)
    {
        if(str_cmp(__DATA_TYPES_INFO__[i][1], q))
            return (_Datatype)__DATA_TYPES_INFO__[i][0];
    }

    return _DT_NULL;
}
