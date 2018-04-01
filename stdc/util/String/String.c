#include "private/private.h"

StringVtable String = {

    // Construction/destruction
    .new        = &new_String,
    .init       = &init_String,
    .del        = &del_String,
    .equals     = &equals_String,

    // Methods
    .set        = &set_String,
    .copy       = &copy_String,
    .size       = &size_String,
    .cstr       = &cstr_String,
    .format     = &format_String

};



