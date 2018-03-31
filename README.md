# StdC
[![Coverage Status](https://coveralls.io/repos/github/ychnlgy/StandardC/badge.svg?branch=master&service=github)](https://coveralls.io/github/ychnlgy/StandardC?branch=master)
[![Build Status](https://travis-ci.org/ychnlgy/StandardC.png)](https://travis-ci.org/ychnlgy/StandardC)
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

Write ```main.c```:
```cpp
// include all headers in stdc:
#include "stdc/lib.h"

int main() {
  return 0;
}
```
Setup project with [CakeBaker](https://github.com/ychnlgy/CakeBaker):
```bash
bakecake.py --init
```
Change ```cake.ini```:
```ini
BUILD_ARGS         = -coverage
COMPILER           = gcc
COMPILE_ARGS       = -Wall -iquote ./ -coverage
DEFAULT_OUTPUTFILE = 
DEFAULT_SOURCEFILE = 
TEST_INCLUDE       = *tests/*_test.cpp *tests/test_*.cpp
TEST_OMIT          = cake .git
```
Compile with [CakeBaker](https://github.com/ychnlgy/CakeBaker):
```bash
bakecake.py main.c app.exe
```
## Examples
| File                                | Description                                                  |
|-------------------------------------|--------------------------------------------------------------|
| [Memory.c](examples/Memory.c)       | How to use Memory to track, allocate and make memory blocks. |
| [List.c](examples/List.c)           | A demonstration of List methods.                             |
| [String.c](examples/String.c)       | A demonstration of String methods.                           |
| [Unittest.c](stdc/util/util_test.c) | How to write a unittest using StdC framework.                |

## Documentation
| Feature                          | Description                                                  |
|----------------------------------|--------------------------------------------------------------|
| [Garbage Collection](doc/gc.md)  | Reference-counting for dynamically allocated objects.        |
| [Memory](doc/Memory.md)          | Acts like a memory stack to reduce use of free and decref.   |
| [List](doc/List.md)              | Dynamically resizing array-list.                             |
| [String](doc/String.md)          | String class for easy and safe string manipulation.          |
| [Utility](doc/util.md)           | Collection of useful functions for dealing with C.           |
| [Types](doc/types.md)            | Several predefined types wrapped in typedef for ease of use. |
| [Unittest](doc/unittest.md)      | Small set of functions for nice looking unittests.           |
