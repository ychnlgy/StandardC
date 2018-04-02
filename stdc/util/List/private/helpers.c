#ifdef STDC_UTIL_LIST_PRIVATE

static void resize(ListObject* this, size_t n) {
    Ptr* data = malloc(n*PTR_SIZE);
    long size = MIN(this->size, n);
    this->size = size;

    while (--size >= 0)
        data[size] = this->data[size];

    free(this->data);

    this->capacity = n;
    this->data = data;
}

static bool isWithin(ListObject* this, long i) {
    return i < this->size && this->size != 0;
}

static long fitWithin(ListObject* this, long i) {
    return MOD(i, this->size);
}

#endif
