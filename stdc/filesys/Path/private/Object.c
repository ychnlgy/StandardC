#ifdef STDC_FILESYS_PATH_PRIVATE

static Ptr new_Path() {
    PathObject* this = new(sizeof(PathObject), &del_Path);
    init_Path(this);
    return this;
}

static void init_Path(PathObject* this) {
    this->isAbs = 0;
    this->name = String.new();
    this->list = List.new();
}

static void del_Path(Ptr ptr) {
    PathObject* this = ptr;
    decref(this->name);
    decref(this->list);
}

static CStr cstr_Path(PathObject* this) {
    return String.cstr(this->name);
}

static StringObject* str_Path(PathObject* this) {
    return this->name;
}

static PathObject* copy_Path(PathObject* this, MemoryObject* mem) {
    PathObject* out = Memory.make(mem, &new_Path);
    if (List.isEmpty(this->list))
        return out;
    out->isAbs = this->isAbs;
    String.set(out->name, String.cstr(this->name));
    List.extend(out->list, this->list);
    return out;
}

static bool equals_Path(PathObject* this, PathObject* other) {
    MemoryObject* mem = Memory.new();
    PathObject* path1 = abs_Path(this, mem);
    PathObject* path2 = abs_Path(other, mem);
    bool result = String.equals(str_Path(path1), str_Path(path2));
    decref(mem);
    return result;
}

#endif
