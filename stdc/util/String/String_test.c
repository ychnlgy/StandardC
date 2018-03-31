#include "stdc/unittest.h"

#include <string.h>

String* s1;
String* s2;

SETUP {
    s1 = new_String();
    s1->_->set(s1, "Hello world!");

    s2 = new_String();
    s2->_->set(s2, "Evil bunny");
}

TEARDOWN {
    decref(s1);
    decref(s2);
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
    
        String* s3 = new_String();
        s3->_->set(s3, "Half");
        ASSERT(s1->_->equals(s1, s3));
        decref(s3);
    END

    CASE("copy")
        String* s3 = s1->_->copy(s1);
        String* s4 = s3->_->copy(s3);
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

        decref(s3);
        decref(s4);
    END

    CASE("get-cstr")
        ASSERT(strcmp(s2->_->cstr(s2), s1->_->cstr(s1)) != 0);
        s2->_->set(s2, "Hello world!");
        ASSERT(strcmp(s2->_->cstr(s2), s1->_->cstr(s1)) == 0);
    END

STOP
