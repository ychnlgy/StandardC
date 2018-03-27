#include "../Memory.h"

#include <stdio.h>
// printf

void* new_int() {
    return new(sizeof(int), &destroy_nothing);
}

int main() {
    printf("Running %s...", __FILE__);
    
    // Old method
    Memory* memory = new_Memory();
    
    int* a = new(sizeof(int), &destroy_nothing);
    int* b = new(sizeof(int), &destroy_nothing);
    
    *a = 4;
    *b = 6;
    
    decref(a);
    decref(b);
    
    free_Memory(memory);
    
    // New ways
    memory = new_Memory();
    
    a = new(sizeof(int), &destroy_nothing);
    track_Memory(memory, &a);
    b = alloc_Memory(memory, sizeof(int), &destroy_nothing);
    int* c = make_Memory(memory, &new_int);
    *c = 10;
    
    
    free_Memory(memory);
    
    printf("OK\n");
}
