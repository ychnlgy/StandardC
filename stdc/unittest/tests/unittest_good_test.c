#include "stdc/unittest.h"

SETUP{}
TEARDOWN{}

RUN
    CASE("Hello")
        ASSERT(2 + 2 == 4);
    END

    CASE("world")
        ASSERT(1 == 1);
    END

STOP
