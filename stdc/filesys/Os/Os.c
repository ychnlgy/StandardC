#include <assert.h>

#include <string.h>
// strlen

#include "Os_private.h"

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

static char* cwd_Os(MemoryObject* mem) {
    char* buf;
    if (mem)
        buf = Memory.alloc(mem, sizeof(char)*BUFSIZE);
    else
        buf = malloc(sizeof(char) * BUFSIZE);
    // getcwd returns NULL if BUFSIZE is inadequate.
    assert(getcwd(buf, BUFSIZE) != NULL);
    return buf;
}

static int chmod_Os(CStr p, CStr cmd) {
    int n = strlen(cmd);
    if (n < 2)
        return -1;
    return chPermission(p, getSetFn(cmd[0]), getMode(cmd, n));
}

// Helpers

/*
 * Adapted from:
 * https://stackoverflow.com/questions/29068909
 * "Removing permissions on a file? C Programming"
 */

static void rmPermission(mode_t* m, mode_t n) {
    *m &= ~n;
}

static void addPermission(mode_t* m, mode_t n) {
    *m |= n;
}

static int chPermission(CStr p,_ChPermissionFn fn, mode_t m) {
    if (fn == NULL || m == -1)
        return -1;
    struct stat st;
    stat(p, &st);
    mode_t mode = st.st_mode & 07777;
    fn(&mode, m);
    chmod(p, mode);
    return 0;
}

static _ChPermissionFn getSetFn(char set) {
    switch (set) {
        case '-':
            return &rmPermission;
        case '+':
            return &addPermission;
        default:
            return NULL;
    }
}

static mode_t getMode(CStr cmd, int n) {
    mode_t m = 0;
    
    int i;
    for (i=1; i<n; i++) {
        char typ = cmd[i];
        switch (typ) {
            case 'r':
                m |= S_IRUSR;
                break;
            case 'w':
                m |= S_IWUSR;
                break;
            default:
                return -1;
        }
    }
    
    return m;
}

