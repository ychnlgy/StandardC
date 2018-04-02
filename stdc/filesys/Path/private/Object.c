#ifdef STDC_FILESYS_PATH_PRIVATE

static Ptr new_Path() {
    PathObject* this = new(sizeof(PathObject), &del_Path);
    init_Path(this);
    return this;
}

static void init_Path(PathObject* this) {
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

static void set_Path(PathObject* this, CStr name) {
    String.set(this->name, name);
    breakCStrPath(this->list, name);
}

#endif
