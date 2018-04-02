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

#endif
