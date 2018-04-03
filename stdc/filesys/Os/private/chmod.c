#ifdef STDC_FILESYS_OS_PRIVATE

#include <string.h>
// strlen

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

static int chmod_Os(CStr p, CStr cmd) {
    int n = strlen(cmd);
    if (n < 2)
        return -1;
    return chPermission(p, getSetFn(cmd[0]), getMode(cmd, n));
}

#endif
