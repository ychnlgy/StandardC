#ifdef STDC_UTIL_STRING_PRIVATE

static long size_String(StringObject* this) {
    return this->size;
}

static bool contains_String(StringObject* this, StringObject* substr) {
    return index_String(this, substr) > -1;
}

#endif
