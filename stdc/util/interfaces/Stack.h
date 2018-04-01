// Interface: inherits Object

typedef struct Stack Stack;

typedef struct {
    AccessorVtable super;
    
    void    (*push)     (Stack*, Ptr);
    Ptr     (*pop)      (Stack*);
    Ptr     (*back)     (Stack*);
} StackVtable;

struct Stack {
    StackVtable* _;
};
