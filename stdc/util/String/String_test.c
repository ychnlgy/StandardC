#include "stdc/lib.h"
#include "stdc/unittest.h"

#include <string.h>

String* s1;
String* s2;

SETUP {
    s1 = new_String();
    s1->set(s1, "Hello world!");

    s2 = new_String();
    s2->set(s2, "Evil bunny");
}

TEARDOWN {
    decref(s1);
    decref(s2);
}

RUN
    CASE("size")
        ASSERT(s1->size(s1) == 12);
        ASSERT(s2->size(s2) == 10);
    END

    CASE("re-set")
        s1->set(s1, "No memory leaks!");
        ASSERT(s1->size(s1) == 16);
        s1->set(s1, "Half");
        ASSERT(!(s1->equals(s1, s2)));
    
        String* s3 = new_String();
        s3->set(s3, "Half");
        ASSERT(s1->equals(s1, s3));
        decref(s3);
    END

    CASE("copy")
        String* s3 = s1->copy(s1);
        String* s4 = s3->copy(s3);
        ASSERT(s3->size(s3) == 12);
        ASSERT(s4->size(s4) == 12);
        ASSERT(s3->equals(s3, s1));
        ASSERT(s4->equals(s4, s1));

        s2->set(s2, "Hello world!");
        ASSERT(s2->equals(s2, s3));
        ASSERT(s2->equals(s2, s1));
        ASSERT(s2->equals(s2, s4));

        s2->set(s2, "Hello world");
        ASSERT(!(s2->equals(s2, s3)));
        ASSERT(!(s2->equals(s2, s1)));
        ASSERT(!(s2->equals(s2, s4)));

        s3->set(s3, "Superman1234");
        ASSERT(s3->size(s3) == 12);
        ASSERT(s4->size(s4) == 12);
        ASSERT(!s3->equals(s3, s4));

        decref(s3);
        decref(s4);
    END

    CASE("get-cstr")
        ASSERT(strcmp(s2->cstr(s2), s1->cstr(s1)) != 0);
        s2->set(s2, "Hello world!");
        ASSERT(strcmp(s2->cstr(s2), s1->cstr(s1)) == 0);
    END

STOP
