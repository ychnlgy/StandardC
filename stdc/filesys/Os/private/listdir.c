#ifdef STDC_FILESYS_OS_PRIVATE

/*
 * Adapted from:
 * http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Simple-Directory-Lister.html
 * "14.2.4 Simple Program to List a Directory"
 */

static ListObject* listdir_Os(CStr dir, MemoryObject* mem) {
    ListObject* out = Memory.make(mem, List.new);
    
    struct dirent* ep;
    DIR* dp = opendir (dir);
    if (dp != NULL) {
        ep = readdir(dp);
        while (ep) {
            StringObject* fname = Memory.make(mem, String.new);
            String.set(fname, ep->d_name);
            
            if (!String.eqCStr(fname, SKIP_PATH) && !String.eqCStr(fname, BACK_PATH))
                List.push(out, fname);
            
            ep = readdir(dp);
        }
        closedir (dp);
    } else {
        return NULL;
    }

    return out;
}

#endif
