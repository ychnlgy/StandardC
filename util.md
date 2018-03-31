# Utility

Small collection of useful macros.

## Files
 * [stdc/util/util.h](../stdc/util/util.h)
 * [stdc/util/util_test.c](../stdc/util/util_test.c)

## MAX(_any1_, _any2_)
Returns the max of the two.

## MIN(_any1_, _any2_)
Returns the min of the two.

## LEN(_arr_)
Returns the size of the array.

## MOD(_a_, _b_)
Returns the positive modulus of a in respect to b.
```c
#include "stdc/lib.h"

int main() {
  int m = MOD(-10, 12); // m == 2;
  return 0;
}
```
