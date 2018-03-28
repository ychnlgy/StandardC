#include "../Memory.h"
#include "../unittest.h"

void* new_int() {
    return new(sizeof(int), &destroy_nothing);
}

int* a;
int* b;
int* c;

SETUP{}
TEARDOWN{}

RUN
    
    CASE("old-method")

        a = new(sizeof(int), &destroy_nothing);
        b = new(sizeof(int), &destroy_nothing);
        c = new_int();
        
        *a = 4;
        *b = 6;
        *c = 10;
        
        decref(&a);
        decref(&b);
        decref(&c);
    
    END
    
    CASE("new-method")
    
        Memory* memory = new_Memory();
        
        a = new(sizeof(int), &destroy_nothing);
        memory->track(memory, &a);
        
        b = memory->alloc(memory, sizeof(int), &destroy_nothing);
        
        c = memory->make(memory, &new_int);
        
        *a = 4;
        *b = 6;
        *c = 10;
        
        del(&memory);
    
    END

STOP
