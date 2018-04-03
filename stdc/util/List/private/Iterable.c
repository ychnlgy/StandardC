#ifdef STDC_UTIL_LIST_PRIVATE

static ListObject* filter_List(ListObject* this, FilterFunc fn, MemoryObject* mem) {
    ListObject* out = Memory.make(mem, List.new);
    
    long i;
    for (i=0; i<this->size; i++) {
        Ptr p = this->data[i];
        if (fn(p))
            push_List(out, p);
    }
    
    return out;
}

#endif
