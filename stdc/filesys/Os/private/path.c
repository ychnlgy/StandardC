#ifdef STDC_FILESYS_OS_PRIVATE

// depends on access function from
// unistd.h (and hopefully direct.h)

static bool canRead_Os(CStr fname) {
    return access(fname, R_OK) != -1;
}

static bool canWrite_Os(CStr fname) {
    return access(fname, W_OK) != -1;
}


static bool isfile_Os(CStr pname) {
    struct stat buf;
    return (stat(pname, &buf) == 0);
/*    return access(fname, F_OK) != -1;*/
}

static bool isdir_Os(CStr pname) {
    return false;
}

#endif
