#ifdef STDC_FILESYS_PATH_PRIVATE

static PathObject* add_Path(PathObject* this, PathObject* other, MemoryObject* mem) {
    PathObject* newp = Memory.make(mem, &new_Path);
    List.extend(newp->list, this->list);
    List.extend(newp->list, other->list);
    decref(newp->name);
    newp->name = String.join(PATH_SEP, newp->list, mem);
    incref(newp->name);
    return newp;
}

static PathObject* abs_Path(PathObject* this, MemoryObject* mem) {
    if (this->isAbs)
        return this;
    
    MemoryObject* submem = Memory.new();
    
    // Inner scope
    CStr cwd = Os.cwd(submem);
    PathObject* out = Memory.make(submem, Path.new);
    setabs_Path(out, cwd);
    out = add_Path(out, this, submem);
    
    // Outer scope
    out = norm_Path(out, mem);

    decref(submem);
    return out;
}

static PathObject* norm_Path(PathObject* this, MemoryObject* mem) {
    MemoryObject* submem = Memory.new();
    ListObject* normed = removePathRedundancy(this->list, submem);
    StringObject* abspath = String.join(PATH_SEP, normed, submem);
    PathObject* newp = Memory.make(mem, &new_Path);
    String.set(newp->name, String.cstr(abspath));
    List.extend(newp->list, this->list);
    decref(submem);
    return newp;
}

#endif
