#include "../RefList.h"
#include "../unittest.h"
#include "../Memory.h"
#include "../gc.h"

List* list;
Memory* mem;

int* i1;
int* i2;
int** p;

SETUP {
    list = new_RefList();
    mem = new_Memory();
    
    // i1, i2 will have ref=1
    i1 = mem->alloc(mem, sizeof(int));
    i2 = mem->alloc(mem, sizeof(int));
    *i1 = 40;
    *i2 = 60;
}

TEARDOWN {
    del(&list);
    del(&mem);
}

RUN

    CASE("get-set")
    
        ASSERT(list->len(list) == 0);
    
        // after pushing, i1, i2 will have ref=2
        list->push(list, &i1);
        list->push(list, &i2);
        
        ASSERT(**((int**) list->getitem(list, 0)) == *i1);
        ASSERT(**((int**) list->getitem(list, 1)) == *i2);
        
        list->setitem(list, 0, &i2);
        ASSERT(**((int**) list->getitem(list, 0)) == *i2);
        ASSERT(**((int**) list->getitem(list, 1)) == *i2);
        
        ASSERT(list->set(list, 1, &i1));
        ASSERT(**((int**) list->getitem(list, 0)) == *i2);
        ASSERT(**((int**) list->getitem(list, 1)) == *i1);
        
        ASSERT(!list->set(list, 2, &i1));
        ASSERT(**((int**) list->getitem(list, 0)) == *i2);
        ASSERT(**((int**) list->getitem(list, 1)) == *i1);
        
        ASSERT(list->len(list) == 2);
        
    END
    
    CASE("push-pop")
    
        list->push(list, &i1);
        list->push(list, &i2);
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(list->len(list) == 1);
        ASSERT(**p == *i2);
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(list->len(list) == 0);
        ASSERT(**p == *i1);
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(p == NULL);
        p = list->pop(list);
        ASSERT(p == NULL);
        
    END
    
    CASE("push-pop refcount")
    
        Memory* mem2 = new_Memory();
        
        int* b1 = mem2->alloc(mem2, sizeof(int));
        int* b2 = mem2->alloc(mem2, sizeof(int));
        
        *b1 = 20;
        *b2 = 30;
        
        list->push(list, &b1);
        list->push(list, &b2);
        // b1, b2 now have ref=2
        
        del(&mem2);
        // b1, b2 now have ref=1
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(*p != NULL);
        ASSERT(**p == *b2);
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(**p == *b1);
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(p == NULL);
        
        p = list->pop(list);
        mem->track(mem, p);
        ASSERT(p == NULL);
    
    END

STOP
