#ifdef STDC_UTIL_STRING_PRIVATE

static StringObject* add_String(StringObject* this, StringObject* other, MemoryObject* mem) {
    StringObject* nstr = Memory.make(mem, String.new);
    long size = this->size + other->size;
    if (size == 0)
        return nstr;
    nstr->size = size;
    nstr->cstr = malloc(sizeof(char)*(size+1));
    long i;
    for (i=0; i<this->size; i++)
        nstr->cstr[i] = this->cstr[i];
    for (i=0; i<other->size; i++)
        nstr->cstr[i+this->size] = other->cstr[i];
    nstr->cstr[size] = '\0';
    nstr->hash = calculateHash(nstr);
    return nstr;
}

#endif
