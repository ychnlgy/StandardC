#include "stdc/unittest.h"

SETUP{}
TEARDOWN{}

RUN
    CASE("MIN-MAX")
        ASSERT(MAX(2, 3) == 3);
        ASSERT(MIN(9, 20) == 9);
    END

    CASE("LEN")
        int is[] = {1, 2, 5, 6, 7};
        ASSERT(LEN(is) == 5);
    END

    CASE("brackets for MIN-MAX")
        ASSERT(1 % MAX(1, 2) == 1);
    END

    CASE("MOD")
        ASSERT(MOD(12, 3) == 0);
        ASSERT(MOD(12, 4) == 0);
        ASSERT(MOD(12, 5) == 2);
        ASSERT(MOD(12, 7) == 5);
        ASSERT(MOD(7, 12) == 7);
        ASSERT(MOD(-7, 12) == 5);
        ASSERT(MOD(-10, 40) == 30);
        ASSERT(MOD(10, 40) == 10);
    END
STOP
