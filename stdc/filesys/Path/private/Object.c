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
    out->isAbs = true;
    String.set(out->name, String.cstr(this->name));
    List.extend(out->list, this->list);
    return out;
}

static bool equals_Path(PathObject* this, PathObject* other) {
    MemoryObject* mem = Memory.new();
    PathObject* path1 = abs_Path(this, mem);
    PathObject* path2 = abs_Path(other, mem);
    
    bool result;
    if (List.size(path1->list) != List.size(path2->list)) {
        result = false;
    } else {
        result = true;
        long i;
        for (i=0; i<List.size(path1->list); i++) {
            StringObject* i1 = List.getitem(path1->list, i);
            StringObject* i2 = List.getitem(path2->list, i);
            if (!String.equals(i1, i2)) {
                result = false;
                break;
            }
        }
    }
    decref(mem);
    return result;
}

#endif
