#ifdef STDC_FILESYS_OS_PRIVATE

// depends on access function from
// unistd.h (and hopefully direct.h)

static bool readable_Os(CStr fname) {
    if (fname == NULL)
        return false;
    return access(fname, R_OK) != -1;
}

static bool writable_Os(CStr fname) {
    if (fname == NULL)
        return false;
    return access(fname, W_OK) != -1;
}

/*
 * Adapted from:
 * "Portable way to check if directory exists [Windows/Linux, C]"
 * https://stackoverflow.com/questions/18100097/
 */

static bool isfile_Os(CStr pname) {
    if (pname == NULL)
        return false;
    struct stat buf;
    if(stat(pname, &buf) != 0)
        return false;
    else if(buf.st_mode & S_IFDIR)
        return false;
    else
        return true;
}

static bool isdir_Os(CStr pname) {
    if (pname == NULL)
        return false;
    struct stat buf;
    if(stat(pname, &buf) != 0)
        return false;
    else if(buf.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

#endif
