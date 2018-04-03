#ifdef STDC_FILESYS_PATH_PRIVATE

static bool isfile_Path(PathObject* this) {
    return false;
}

static bool isdir_Path(PathObject* this) {
    return false;
}

static ListObject* listdir_Path(PathObject* this, MemoryObject* mem) {
    return NULL;
}

static void setrel_Path(PathObject* this, CStr name) {
    setpath(this, name, false);
}

static void setabs_Path(PathObject* this, CStr name) {
    setpath(this, name, true);
}

static void setrelstr_Path(PathObject* this, StringObject* name) {
    setpath(this, String.cstr(name), false);
}

static void setabsstr_Path(PathObject* this, StringObject* name) {
    setpath(this, String.cstr(name), true);
}

#endif
