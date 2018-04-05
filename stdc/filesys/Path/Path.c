#include "Path_private.h"

PathVtable Path = {
    .new        = &new_Path,
    .init       = &init_Path,
    .del        = &del_Path,
    
    // Object
    .cstr       = &cstr_Path,
    .str        = &str_Path,
    .equals     = &equals_Path,
    .copy       = &copy_Path,
    
    // Numeric
    .add        = &add_Path,
    .abs        = &abs_Path,
    .norm       = &norm_Path,
    
    // Path
    .addcstr    = &addcstr_Path,
    .isfile     = &isfile_Path,
    .isdir      = &isdir_Path,
    .listdir    = &listdir_Path,
    .setrel     = &setrel_Path,
    .setabs     = &setabs_Path,
    .setrelstr  = &setrelstr_Path,
    .setabsstr  = &setabsstr_Path,
    .dirname    = &dirname_Path,
    .basename   = &basename_Path
};

static char PATH_SEP = '/';
static char BAD_SEP = '\\';
static CStr SKIP_PATH = ".";
static CStr BACK_PATH = "..";

// Helpers
static void breakCStrPath(ListObject* pathlist, CStr name) {
    MemoryObject* mem = Memory.new();

    StringObject* sname = Memory.make(mem, String.new);
    String.set(sname, name);

    // remove terminating PATH_SEP if necessary
    if (String.size(sname) > 0) {
        char* c = String.at(sname, -1);
        if (*c == PATH_SEP || *c == BAD_SEP)
            sname = String.slice(sname, 0, String.size(sname)-1, mem);
    }

    StringObject* normalized = String.replace(sname, BAD_SEP, PATH_SEP, mem);
    ListObject* list = String.split(normalized, PATH_SEP, mem);
    
    List.clear(pathlist);
    List.extend(pathlist, list);
    
    decref(mem);
}

static void setpath(PathObject* this, CStr name, bool isAbs) {
    this->isAbs = isAbs;
    String.set(this->name, name);
    breakCStrPath(this->list, name);
}

static bool isSkipPath(Ptr ptr) {
    return !String.eqCStr(ptr, SKIP_PATH);
}

static ListObject* removeBack(ListObject* list, MemoryObject* scope) {
    ListObject* out = List.new();
    
    long canpop = 0;
    long i;
    for (i=0; i<List.size(list); i++) {
        StringObject* s = List.getitem(list, i);
        if (String.eqCStr(s, BACK_PATH)) {
            if (canpop > 0) {
                canpop--;
                List.pop(out, scope);
                
            } else {
                List.push(out, s);
            }
        } else {
            canpop++;
            List.push(out, s);
        }
    }
    
    return out;
}

static ListObject* removePathRedundancy(ListObject* list, MemoryObject* mem) {
    MemoryObject* scope = Memory.new();
    ListObject* noSkip = List.filter(list, &isSkipPath, scope);
    ListObject* result = removeBack(noSkip, scope);
    Memory.track(mem, result); // keep result alive in lower scope.
    decref(scope);
    return result;
}

static PathObject* normalize(ListObject* newl, bool isAbs, MemoryObject* mem) {
    MemoryObject* scope = Memory.new();
    Memory.track(scope, newl);
    
    PathObject* newp = new(sizeof(PathObject), &del_Path);
    Memory.track(mem, newp);
    
    newp->isAbs = isAbs;
    newp->list = removePathRedundancy(newl, scope);
    newp->name = String.join(PATH_SEP, newp->list, scope);
    incref(newp->name);
    incref(newp->list);
    
    decref(scope);
    return newp;
}

// Object
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

// Numeric
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

// Path
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
    ListObject* dir = Os.listdir(Path.cstr(this), mem);
    if (dir == NULL)
        return NULL;
    
    ListObject* out = Memory.make(mem, List.new);
    long i;
    for (i=0; i<List.size(dir); i++) {
        StringObject* f = List.getitem(dir, i);
        PathObject* p = addcstr_Path(this, String.cstr(f), mem);
        List.push(out, p);
    }
    return out;
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

static StringObject* basename_Path(PathObject* this) {
    if (List.size(this->list) > 0)
        return List.back(this->list);
    else
        return NULL;
}
