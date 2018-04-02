#ifdef STDC_UTIL_STRING_PRIVATE

static long hash_String(StringObject* this) {
    return this->hash;
}

/*
 * FNV-1a algorithm copied from:
 * http://isthe.com/chongo/tech/comp/fnv/
 * April 1, 2018.
 */

static long FNV_PRIME    = 16777619;
static long OFFSET_BASIS = 2166136261;

static long calculateHash(StringObject* this) {
    long hash = OFFSET_BASIS;
    long i;
    for (i=0; i<this->size; i++)
        hash = (this->cstr[i] ^ hash) * FNV_PRIME;
    return hash;
}

#endif
