#include "../algorithm.h"

#include <stdio.h>
#include <assert.h>

int main() {
    printf("Running %s...", __FILE__);
    
    assert(max(2, 3) == 3);
    assert(min(9, 20) == 9);
    
    int is[] = {1, 2, 5, 6, 7};
    assert(len(is) == 5);
    
    printf("OK\n");
}
