# StdC
[![Coverage Status](https://coveralls.io/repos/github/ychnlgy/StandardC/badge.svg?branch=master&service=github)](https://coveralls.io/github/ychnlgy/StandardC?branch=master)
[![Build Status](https://travis-ci.org/ychnlgy/StandardC.png)](https://travis-ci.org/ychnlgy/StandardC)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

C Standard Library.

## Installation using [```git-install```](https://github.com/ychnlgy/GitInstaller)
```bash
git-install.py ychnlgy/StdC
```

## Uninstall using [```git-install```](https://github.com/ychnlgy/GitInstaller)
```bash
git-install.py --uninstall ychnlgy/StdC
```

## Quickstart
```cpp
// include all headers in stdc:
#include "stdc/lib.h"

int main() {
  return 0;
}
```

## Examples
| File                          | Description                                                  |
|-------------------------------|--------------------------------------------------------------|
| [Memory.c](examples/Memory.c) | How to use Memory to track, allocate and make memory blocks. |
| [List.c](examples/List.c)     | A demonstration of List methods.                             |

## Documentation
| Feature                          | Description                                                  |
|----------------------------------|--------------------------------------------------------------|
| [Garbage collection](doc/gc.md)  | Memory management to reduce the use of free.                 |
| [List](doc/List.md)              | Dynamically resizing array-list.                             |
