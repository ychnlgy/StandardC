#include "private/private.h"

StringVtable String = {

    // Construction/destruction
    .new        = &new_String,
    .init       = &init_String,
    .del        = &del_String,
    
    // Object
    .equals     = &equals_String,
    .cstr       = &cstr_String,
    .copy       = &copy_String,
    
    // Hashable
    .hash       = &hash_String,
    
    // Numeric
    .add        = &add_String,

    // Container
    .size       = &size_String,
    .contains   = &contains_String,
    
    // Accessor
    .set        = &set_String,
    .getitem    = &getitem_String,
    .at         = &at_String,
    .slice      = &slice_String,
    .index      = &index_String,
    
    // String
    .format     = &format_String,
    .startswith = &startswith_String,
    .endswith   = &endswith_String,
    .rstrip     = &rstrip_String,
    .lstrip     = &lstrip_String,
    .strip      = &strip_String,
    .split      = &split_String,
    .splitstr   = &splitstr_String

};



