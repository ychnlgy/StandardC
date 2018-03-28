#include "../Memory.h"
#include "../unittest.h"
#include "../gc.h"

void* new_int() {
    return new(sizeof(int), &destroy_nothing);
}

int* a;
int* b;
int* c;

Memory* memory;

SETUP{
    memory = new_Memory();
}

TEARDOWN{
    del(&memory);
}

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
        
        a = new(sizeof(int), &destroy_nothing);
        memory->track(memory, &a);
        
        b = memory->alloc(memory, sizeof(int));
        
        c = memory->make(memory, &new_int);
        
        *a = 4;
        *b = 6;
        *c = 10;
    
    END
    
    CASE("track NULL")
    
        a = memory->alloc(memory, sizeof(int));
        b = memory->alloc(memory, sizeof(int));
        c = new_int();
        int* d = new_int();
        memory->track(memory, &c);
        memory->track(memory, &d);
        memory->track(memory, NULL);
        memory->track(memory, NULL);
    
    END

STOP
