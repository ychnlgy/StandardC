#ifdef STDC_MEMORY_MEMORY_PRIVATE

static void track_Memory(MemoryObject* this, Ptr ptr) {
    if (ptr != NULL)
        List.push(this->scope, ptr);
}

static Ptr alloc_Memory(MemoryObject* this, size_t typesize) {
    Ptr ptr = new(typesize, NULL);
    track_Memory(this, ptr);
    return ptr;
}

static Ptr make_Memory(MemoryObject* this, Maker maker) {
    Ptr ptr = maker();
    track_Memory(this, ptr);
    return ptr;
}

#endif
