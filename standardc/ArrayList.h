#ifndef STANDARD_ARRAYLIST
#define STANDARD_ARRAYLIST

typedef struct ArrayList ArrayList;

void* new_ArrayList();

// Init
void init_ArrayList(ArrayList* this, int typesize);
void initall_ArrayList(ArrayList* this, int typesize, int len, void* value);
void initarray_ArrayList(ArrayList* this, int typesize, int len, void* array);

// Getters
int len_ArrayList(ArrayList* this);

// Modifiers
void push_ArrayList(ArrayList* this, void* item);
void* pop_ArrayList(ArrayList* this);

// Fast but unsafe operations (does not check range).
void* getitem_ArrayList(ArrayList* this, int i);
void setitem_ArrayList(ArrayList* this, int i, void* item);

// Slow but safe operations.(checks range).
void* at_ArrayList(ArrayList* this, int i);
void set_ArrayList(ArrayList* this, int i, void* item);

// Iteration
void foreach_ArrayList(ArrayList* this, void(*fn)(void*));
//ArrayList* map_ArrayList(ArrayList*

#endif
