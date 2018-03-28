#ifndef STANDARD_ARRAYLIST
#define STANDARD_ARRAYLIST

void* new_ArrayList();

typedef struct ArrayListFields ArrayListFields;
typedef struct ArrayList ArrayList;

struct ArrayList {
    ArrayListFields* fields;
    
    // Init
    void    (*init)         (ArrayList*, int);
    void    (*initall)      (ArrayList*, int, int, void*);
    void    (*initarray)    (ArrayList*, int, int, void*);
    
    // Getters
    int     (*len)          (ArrayList*);
    
    // Modifiers
    void    (*push)         (ArrayList*, void*);
    void*   (*pop)          (ArrayList*);
    
    // Fast but unsafe accessors (does not check range)
    void*   (*getitem)      (ArrayList*, int);
    void    (*setitem)      (ArrayList*, int, void*);
    
    // Slow but safe accessors (checks for range)
    void*   (*at)           (ArrayList*, int);
    
    // Iteration
    void    (*foreach)      (ArrayList*, void(*)(void*));
    
};

#endif
