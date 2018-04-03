#ifdef STDC_FILESYS_PATH_PRIVATE

static PathObject* addcstr_Path(PathObject* this, CStr cstr, MemoryObject* mem) {
    ListObject* newl = List.new();
    ListObject* temp = List.new();
    breakCStrPath(temp, cstr);
    List.extend(newl, this->list);
    List.extend(newl, temp);
    decref(temp);
    
    return normalize(newl, this->isAbs, mem);
}

static bool isfile_Path(PathObject* this) {
    return Os.isfile(String.cstr(this->name));
}

static bool isdir_Path(PathObject* this) {
    return Os.isdir(String.cstr(this->name));
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

static PathObject* dirname_Path(PathObject* this, MemoryObject* mem) {
    if (List.size(this->list) == 0)
        return Memory.make(mem, &new_Path);

    ListObject* newl = List.slice(this->list, mem, 0, List.size(this->list)-1);
    incref(newl);
    return normalize(newl, this->isAbs, mem);
}

#endif
