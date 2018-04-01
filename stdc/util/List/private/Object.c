#ifdef STDC_UTIL_LIST_PRIVATE

static Ptr new_List() {
    ListObject* this = new(sizeof(List), &del_List);
    init_List(this);
    return this;
}

static void init_List(ListObject* this) {
    this->size     = 0;
    this->capacity = MIN_CAPACITY;
    this->data     = malloc(MIN_CAPACITY*PTR_SIZE);
}

static void del_List(Ptr ptr) {
    ListObject this = *((ListObject*) ptr);
    long i;
    for (i=0; i<this.size; i++)
       decref(this.data[i]);
    free(this.data);
}

static bool equals_List(ListObject* this, ListObject* other) {
    if (this->size != other->size)
        return false;
    
    long i;
    for (i=0; i<this->size; i++)
        if (this->data[i] != other->data[i])
            return false;
    return true;
}

#endif
