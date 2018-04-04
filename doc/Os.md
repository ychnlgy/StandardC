# Os

Collection of low-level operating system calls.

## Methods chart
| Interface | Method |
|-----------|--------|
| Os | ```char* Os.cwd(MemoryObject* mem);``` |
|    | ```bool Os.readable(CStr fname);``` |
|    | ```bool Os.writable(CStr fname);``` |
|    | ```bool Os.isfile(CStr fname);``` |
|    | ```bool Os.isdir(CStr fname);``` |
|    | ```ListObject* Os.listdir(CStr fname, MemoryObject* mem);``` |
|    | ```int Os.chmod(CStr fname, CStr cmd);``` |

## Files
 * [stdc/filesys/Os/Os.h](../stdc/filesys/Os/Os.h)

## Demonstration
```c
#include "stdc/lib.h"
#include <stdio.h>

int main() {
  char* cwd = Os.cwd(NULL); // Os does not have the "new" method
                            // because it is not a class.
  printf("%s\n", cwd);
  free(cwd);
}
```
## Os
#### Os.cwd(_mem_)
```c
char* Os.cwd(MemoryObject* mem);
```
Returns the CStr of the current working directory. 

If **mem** is ```NULL```, you must free the returned pointer.

#### Os.readable(_fname_)
```c
bool Os.readable(CStr fname);
```
Returns true if **fname** is the name of a file and the file has permission to be read.

#### Os.writable(_fname_)
```c
bool Os.writable(CStr fname);
```
Returns true if **fname** is the name of a file and the file has permission to be written in.

#### Os.isfile(_fname_)
```c
bool Os.isfile(CStr fname);
```
Returns true if **fname** is the name of a file.

#### Os.isdir(_fname_)
```c
bool Os.isdir(CStr fname);
```
Returns true if **fname** is the name of a directory.

#### Os.listdir(_fname_, _mem_)
```c
ListObject* Os.listdir(CStr fname, MemoryObject* mem);
```
Returns a ListObject of StringObjects representing the names of filesystem components within the directory **fname**. 
This differs from the result of [```Path.listdir```](Path.md).

#### Os.chmod(_fname_, _cmd_)
```c
int Os.chmod(CStr fname, CStr cmd);
```
Changes the permissions of **fname** file.

It returns ```-1``` if no action was taken (i.e. bad input).
