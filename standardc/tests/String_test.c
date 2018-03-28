#include "../String.h"
#include "../gc.h"
#include "../unittest.h"

String* s1;
String* s2;

SETUP {
    s1 = new_String();
    s1->init(s1, "Hello world!");
    
    s2 = new_String();
    s2->init(s2, "Evil bunny");
}

TEARDOWN {
    del(s1);
    del(s2);
}

RUN
    CASE("len")
        ASSERT(s1->len(s1) == 12);
        ASSERT(s2->len(s2) == 10);
    END
    
    CASE("re-init")
        s1->init(s1, "No memory leaks!");
        ASSERT(s1->len(s1) == 16);
        s1->init(s1, "Half");
        ASSERT(!(s1->equals(s1, s2)));
        
        String* s3 = new_String();
        s3->init(s3, "Half");
        ASSERT(s1->equals(s1, s3));
        del(s3);
    END
    
    CASE("copy")
        String* s3 = s1->copy(s1);
        ASSERT(s3->len(s3) == 12);
        ASSERT(s3->equals(s3, s1));
        
        s2->init(s2, "Hello world!");
        ASSERT(s2->equals(s2, s3));
        ASSERT(s2->equals(s2, s1));
        
        s2->init(s2, "Hello world");
        ASSERT(!(s2->equals(s2, s3)));
        ASSERT(!(s2->equals(s2, s1)));
        
        del(s3);
    END
STOP
