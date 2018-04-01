#include "stdc/unittest.h"

#include <string.h>

String* s1;
String* s2;
Memory* mem;

SETUP {
    mem = new_Memory();
    s1 = mem->_->make(mem, &new_String);
    s1->_->set(s1, "Hello world!");

    s2 = mem->_->make(mem, &new_String);
    s2->_->set(s2, "Evil bunny");
}

TEARDOWN {
    decref(mem);
}

RUN
    CASE("size")
        ASSERT(s1->_->size(s1) == 12);
        ASSERT(s2->_->size(s2) == 10);
    END

    CASE("re-set")
        s1->_->set(s1, "No memory leaks!");
        ASSERT(s1->_->size(s1) == 16);
        s1->_->set(s1, "Half");
        ASSERT(!(s1->_->equals(s1, s2)));
    
        String* s3 = mem->_->make(mem, &new_String);
        s3->_->set(s3, "Half");
        ASSERT(s1->_->equals(s1, s3));
    END

    CASE("copy")
        String* s3 = s1->_->copy(s1);
        mem->_->track(mem, s3);
        String* s4 = s3->_->copy(s3);
        mem->_->track(mem, s4);
        ASSERT(s3->_->size(s3) == 12);
        ASSERT(s4->_->size(s4) == 12);
        ASSERT(s3->_->equals(s3, s1));
        ASSERT(s4->_->equals(s4, s1));

        s2->_->set(s2, "Hello world!");
        ASSERT(s2->_->equals(s2, s3));
        ASSERT(s2->_->equals(s2, s1));
        ASSERT(s2->_->equals(s2, s4));

        s2->_->set(s2, "Hello world");
        ASSERT(!(s2->_->equals(s2, s3)));
        ASSERT(!(s2->_->equals(s2, s1)));
        ASSERT(!(s2->_->equals(s2, s4)));

        s3->_->set(s3, "Superman1234");
        ASSERT(s3->_->size(s3) == 12);
        ASSERT(s4->_->size(s4) == 12);
        ASSERT(!s3->_->equals(s3, s4));

    END

    CASE("get-cstr")
        ASSERT(strcmp(s2->_->cstr(s2), s1->_->cstr(s1)) != 0);
        s2->_->set(s2, "Hello world!");
        ASSERT(strcmp(s2->_->cstr(s2), s1->_->cstr(s1)) == 0);
    END
    
    CASE("format")
        s1->_->set(s1, "%d - %d + %d = %s");
        
        String* s3 = s1->_->format(s1, 12, 3, 2000, "Answer");
        mem->_->track(mem, s3);
        
        int d = strlen(s3->_->cstr(s3));
        ASSERT(s3->_->size(s3) == d);
        
        String* s4 = mem->_->make(mem, &new_String);
        s4->_->set(s4, "12 - 3 + 2000 = Answer");
        
        ASSERT(s4->_->equals(s4, s3));
        ASSERT(!s4->_->equals(s4, s1));
        ASSERT(!s3->_->equals(s3, s1));
        ASSERT(!s4->_->equals(s4, s2));
        ASSERT(!s3->_->equals(s3, s2));
    END

STOP
