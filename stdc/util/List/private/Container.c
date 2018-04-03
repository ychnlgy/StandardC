#ifdef STDC_UTIL_LIST_PRIVATE

static long size_List(ListObject* this) {
    return this->size;
}

static void clear_List(ListObject* this) {
    del_List(this);
    init_List(this);
}

static bool isEmpty_List(ListObject* this) {
    return this->size == 0;
}

#endif
