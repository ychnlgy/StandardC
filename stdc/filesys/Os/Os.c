#include "private/private.h"

OsVtable Os = {
    // cwd
    .cwd        = &cwd_Os,
    
    // path
    .canRead    = &canRead_Os,
    .canWrite   = &canWrite_Os,
    .isfile     = &isfile_Os,
    .isdir      = &isdir_Os
};
