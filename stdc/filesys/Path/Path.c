#include "private/private.h"

PathVtable Path = {
    .new        = &new_Path,
    .init       = &init_Path,
    .del        = &del_Path,
    
    // Object
    .cstr       = &cstr_Path,
    .str        = &str_Path,
    .equals     = &equals_Path,
    .copy       = &copy_Path,
    
    // Numeric
    .add        = &add_Path,
    .abs        = &abs_Path,
    .norm       = &norm_Path,
    
    // Path
    .addcstr    = &addcstr_Path,
    .isfile     = &isfile_Path,
    .isdir      = &isdir_Path,
    .listdir    = &listdir_Path,
    .setrel     = &setrel_Path,
    .setabs     = &setabs_Path,
    .setrelstr  = &setrelstr_Path,
    .setabsstr  = &setabsstr_Path,
    .dirname    = &dirname_Path
};
