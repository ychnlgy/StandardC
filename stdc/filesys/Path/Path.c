#include "private/private.h"

PathVtable Path = {
    .new        = &new_Path,
    .init       = &init_Path,
    .del        = &del_Path,
    
    // Object
    .cstr       = &cstr_Path,
    .str        = &str_Path,
    .set        = &set_Path,
    
    // Numeric
    .add        = &add_Path,
    .abs        = &abs_Path,
    .norm       = &norm_Path,
    
    // Path
    .isfile     = &isfile_Path,
    .isdir      = &isdir_Path,
    .listdir    = &listdir_Path
};
