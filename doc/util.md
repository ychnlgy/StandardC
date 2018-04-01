# Utility

Small collection of useful macros.

## Files
 * [stdc/util/util.h](../stdc/util/util.h)

## MAX(_a_, _b_)
Returns max{a, b}.

## MIN(_a_, _b_)
Returns min{a, b}.

## LEN(_arr_)
Returns the length of **arr**.

## MOD(_a_, _b_)
Returns the positive modulus of **a** in respect to **b**.
```c
#include "stdc/lib.h"

int main() {
  int m = MOD(-10, 12); // m == 2
  return 0;
}
```
