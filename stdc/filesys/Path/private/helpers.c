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

#endif
