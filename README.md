# StdC
[![Coverage Status](https://coveralls.io/repos/github/ychnlgy/StdC/badge.svg?branch=master)](https://coveralls.io/github/ychnlgy/StdC?branch=master)
[![Build Status](https://travis-ci.org/ychnlgy/StdC.png)](https://travis-ci.org/ychnlgy/StdC)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

C Standard Library. Synergizes with [CakeBaker](https://github.com/ychnlgy/CakeBaker).

## Installation using [```git-install```](https://github.com/ychnlgy/GitInstaller)
```bash
git-install.py ychnlgy/StdC
```

## Uninstall using [```git-install```](https://github.com/ychnlgy/GitInstaller)
```bash
git-install.py --uninstall ychnlgy/StdC
```

## Quickstart

 1. Write ```main.c```:
```cpp
// include all headers in stdc:
#include "stdc/lib.h"

int main() {
  return 0;
}
```
 2. Write the file ```cake.ini``` (copy-paste the following):
```ini
BUILD_ARGS         = -coverage
COMPILER           = gcc
COMPILE_ARGS       = -Wall -iquote ./ -coverage
DEFAULT_OUTPUTFILE = 
DEFAULT_SOURCEFILE = 
TEST_INCLUDE       = *_test.c
TEST_OMIT          = cake .git
```
 3. Compile with [CakeBaker](https://github.com/ychnlgy/CakeBaker):
```bash
bakecake.py main.c app.exe
```

## Documentation
| Feature                          | Description                                                  |
|----------------------------------|--------------------------------------------------------------|
| [Garbage Collection](doc/gc.md)  | Reference-counting for dynamically allocated objects.        |
| [Memory](doc/Memory.md)          | Acts like a memory stack to reduce use of free and decref.   |
| [List](doc/List.md)              | Dynamically resizing array-list.                             |
| [String](doc/String.md)          | String class for easy and safe string manipulation.          |
| [Utility](doc/util.md)           | Collection of useful functions for dealing with C.           |
| [Types](stdc/util/types.h)       | Several predefined types wrapped in typedef for ease of use. |
| [Unittest](doc/unittest.md)      | Small set of functions for nice looking unittests.           |

## Examples
| Feature | Description |
|---------|--------------------------------------------------------------|
| Memory  | [How to use Memory to track, allocate and make memory blocks.](examples/Memory_example.c) |
| List    | [Basic](examples/ListAndMemory1_example.c) and [advanced](examples/ListAndMemory2_example.c) demonstrations of List methods. |
| String  | [A demonstration of String methods.](examples/String_example.c) |
| Unittest | [How to write a unittest using StdC framework.](stdc/unittest/unittest_fail11of17_test.c) |

## Note
All code in this package compiled without errors or warnings on my machine.
If you encountered any compilation problems, 
please write a GitHub issue so I can fix it.
