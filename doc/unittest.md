# Unittest

C unittest framework.

## Files
 * [stdc/unittest.h](../stdc/unittest.h)
 * [stdc/unittest/unittest.h](../stdc/unittest/unittest.h)
 * [stdc/unittest/unittest.c](../stdc/unittest/unittest.c)
 * [stdc/unittest/unittest_good_test.c](../stdc/unittest/unittest_good_test.c)
 * [stdc/unittest/unittest_fail11of17_test.c](../stdc/unittest/unittest_fail11of17_test.c)
 * [stdc/unittest/print.h](../stdc/unittest/print.h)
 * [stdc/unittest/print.c](../stdc/unittest/print.c)
 * [stdc/unittest/print_test.c](../stdc/unittest/print_test.c)

## Demonstration
```c
#include "stdc/unittest.h"

int* i;

SETUP {
  i = malloc(sizeof(int)*2);
}

TEARDOWN {
  free(i);
}

RUN

  CASE("set pointer")
    *i = 4;
    ASSERT(*i == 4);
  END
  
  CASE("add pointer")
    *(i+1) = 4;
    ASSERT(i[1] == 4);
  END
  
STOP
```

## ASSERT(_expression_)
Assert if the expression is true.

## SETUP
Define the setup function that is run before every case.
You must define this function whether or not you have anything to setup/teardown.

## TEARDOWN
Define the teardown function that is run after every case.
You must define this function whether or not you have anything to setup/teardown.

## RUN
Signals the beginning of the test suite.

## STOP
Signals the end of the test suite.

## CASE(_casename_)
The [CStr](../stdc/util/types.h) name of the test case.

## END
Signals the end of the test case.

## Additional macros that are usually not useful

### SYSTEM_EXIT
Define this to be 0 if you would not like the program to terminate with code 1 in the case of any error.

**Define this prior to including ```stdc/unittest.h```.**
```c
#define SYSTEM_EXIT 0
#include "stdc/unittest.h"

SETUP{}
TEARDOWN{}

RUN
  CASE("always fail")
    ASSERT(false); // will no longer cause the program to exit with code 1.
  END
STOP
```

### MAX_LINES
Define this to be a larger number if your unittest file is over 1000 lines.

**Define this prior to including ```stdc/unittest.h```.**
```c
#define MAX_LINES 2000
#include "stdc/unittest.h"

SETUP{}
TEARDOWN{}

RUN
  CASE("I should consider breaking this file into smaller files")
    // Insert 1500 lines here (not recommended).
  END
STOP
```
