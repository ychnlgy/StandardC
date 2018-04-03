#ifdef STDC_FILESYS_PATH_PRIVATE

static PathObject* add_Path(PathObject* this, PathObject* other, MemoryObject* mem) {
    ListObject* newl = List.new();
    List.extend(newl, this->list);
    List.extend(newl, other->list);
    return normalize(newl, this->isAbs, mem);
}

static PathObject* abs_Path(PathObject* this, MemoryObject* mem) {
    if (this->isAbs)
        return this;

    char* cwd = Os.cwd(NULL);
    
    ListObject* newl = List.new();
    breakCStrPath(newl, cwd);
    free(cwd);
    
    List.extend(newl, this->list);
    
    return normalize(newl, true, mem);
}

static PathObject* norm_Path(PathObject* this, MemoryObject* mem) {
    incref(this->list);
    return normalize(this->list, this->isAbs, mem);
}

#endif
