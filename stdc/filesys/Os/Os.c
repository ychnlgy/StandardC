#include "private/private.h"

OsVtable Os = {
    // cwd
    .cwd        = &cwd_Os,
    
    // path
    .readable   = &readable_Os,
    .writable   = &writable_Os,
    .isfile     = &isfile_Os,
    .isdir      = &isdir_Os,
    
    // listdir
    .listdir    = &listdir_Os,
    
    // chmod
    .chmod      = &chmod_Os
};
