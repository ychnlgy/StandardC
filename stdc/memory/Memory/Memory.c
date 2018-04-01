#include "private/private.h"

MemoryVtable Memory = {

    // Construction/destruction
    .new   = &new_Memory,
    .init  = &init_Memory,
    .del   = &del_Memory,
    
    // Methods
    .track = &track_Memory,
    .alloc = &alloc_Memory,
    .make  = &make_Memory

};
