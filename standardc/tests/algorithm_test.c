#include "../algorithm.h"
#include "../unittest.h"

SETUP{}
TEARDOWN{}

RUN
    CASE("min-max")
        ASSERT(max(2, 3) == 3);
        ASSERT(min(9, 20) == 9);
    END
    
    CASE("len")
        int is[] = {1, 2, 5, 6, 7};
        ASSERT(len(is) == 5);
    END
STOP
