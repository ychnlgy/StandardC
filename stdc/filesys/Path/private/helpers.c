#ifdef STDC_FILESYS_PATH_PRIVATE

static void breakCStrPath(ListObject* pathlist, CStr name) {
    MemoryObject* mem = Memory.new();

    StringObject* sname = Memory.make(mem, String.new);
    String.set(sname, name);
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

#endif
