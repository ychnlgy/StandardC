# Path

For navigating and examining the properties of elements in filesystems.

## Methods chart
| Interface | Method |
|-----------|--------|
| Object | ```Ptr Path.new();``` |
|        | ```CStr Path.cstr(PathObject* this);``` |
|        | ```StringObject* Path.str(PathObject* this);``` |
|        | ```bool Path.equals(PathObject* this, PathObject* other);``` |
|        | ```PathObject* Path.copy(PathObject* this, MemoryObject* mem);``` |
| Numeric | ```PathObject* Path.add(PathObject* this, PathObject* other, MemoryObject* mem);``` |
|         | ```PathObject* Path.abs(PathObject* this, MemoryObject* mem);``` |
|         | ```PathObject* Path.norm(PathObject* this, MemoryObject* mem);``` |
| Path | ```PathObject* Path.addcstr(PathObject* this, CStr cstr, MemoryObject* mem);``` |
|      | ```bool Path.isfile(PathObject* this);``` |
|      | ```bool Path.isdir(PathObject* this);``` |
|      | ```ListObject* Path.listdir(PathObject* this, MemoryObject* mem);``` |
|      | ```void Path.setrel(PathObject* this, CStr relativePathName);``` |
|      | ```void Path.setabs(PathObject* this, CStr absolutePathName);``` |
|      | ```void Path.setrelstr(PathObject* this, StringObject* relativePathString);``` |
|      | ```void Path.setabsstr(PathObject* this, StringObject* absolutePathString);``` |
|      | ```PathObject* Path.dirname(PathObject* this, MemoryObject* mem);``` |
|      | ```StringObject* Path.basename(PathObject* this);``` |

## Files
 * [stdc/filesys/Path/Path.h](../stdc/filesys/Path/Path.h)
 * [stdc/filesys/Path/protected.h](../stdc/filesys/Path/protected.h)

## Demonstration
```c
#include "stdc/lib.h"
#include <assert.h>

int main() {
  MemoryObject* mem = Memory.new();
  
  PathObject* p1 = Memory.make(mem, Path.new);
  Path.setrel(p1, "./folder/../../sub/./file.c");
  
  PathObject* p2 = Memory.make(mem, Path.new);
  Path.setrel(p2, "../sub/file.c");
  
  assert(Path.equals(p1, p2));
  
  decref(mem);
}
```

## Object
#### Path.new()
```c
Ptr Path.new();
```
Returns the pointer to a new PathObject allocated on heap memory.

#### Path.cstr(_this_)
```c
CStr Path.cstr(PathObject* this);
```
Returns the CStr representing **this** path.

#### Path.str(_this_)
```c
StringObject* Path.str(PathObject* this);
```
Returns the StringObject representing **this** path.

#### Path.equals(_this_, _otherpath_)
```c
bool Path.equals(PathObject* this, PathObject* other);
```
Returns true if the absolute path of **this** equals the absolute path of **other**.

#### Path.copy(_this_, _mem_)
```c
PathObject* Path.copy(PathObject* this, MemoryObject* mem);
```
Returns the pointer to a copy of **this** path made on heap memory.

## Numeric
#### Path.add(_this_, _otherpath_, _mem_)
```c
PathObject* Path.add(PathObject* this, PathObject* other, MemoryObject* mem);
```
Returns a pointer to the new PathObject formed when concatenating **this** path 
to **other** with the path separator ```/```.
```c
#include "stdc/lib.h"

int main() {
  MemoryObject* mem = Memory.new();
  
  PathObject* p1 = Memory.make(mem, Path.new);
  Path.setrel(p1, "folder/sub");
  
  PathObject* p2 = Memory.make(mem, Path.new);
  Path.setrel(p2, "inner/file.c");
  
  PathObject* p3 = Path.add(p1, p2, mem);
  PathObject* p4 = Memory.make(mem, Path.new);
  Path.setrel(p4, "folder/sub/inner/file.c");
  assert(Path.equals(p4, p3));
  
  decref(mem);
}
```
#### Path.norm(_this_, _mem_)
```c
PathObject* Path.norm(PathObject* this, MemoryObject* mem);
```
Returns the normalized path of **this**.

#### Path.abs(_this_, _mem_)
```c
PathObject* Path.abs(PathObject* this, MemoryObject* mem);
```
Returns the absolute, normalized path of **this**.

## Path
#### Path.addcstr(_this_, _pathname_, _mem_)
```c
PathObject* Path.addcstr(PathObject* this, CStr cstr, MemoryObject* mem);
```
Returns a new path formed by concatenating **this** path and **cstr** path name
with the path separator ```/```.

#### Path.isfile(_this_)
```c
bool Path.isfile(PathObject* this);
```
Returns true if **this** is an existing file.

#### Path.isdir(_this_)
```c
bool Path.isdir(PathObject* this);
```
Returns true if **this** is an existing directory.

#### Path.listdir(_this_, _mem_)
```c
ListObject* Path.listdir(PathObject* this, MemoryObject* mem);
```
Returns the ListObject of PathObjects representing the filesystem components in **this** directory.

Returns ```NULL``` if **this** is not a directory.

#### Path.setrel(_this_, _relativePathName_)
```c
void Path.setrel(PathObject* this, CStr relativePathName);
```
Sets this path to the **relativePathName**. Labels the path as relative.

#### Path.setabs(_this_, _absolutePathName_)
```c
void Path.setabs(PathObject* this, CStr absolutePathName);
```
Sets this path to the **absolutePathName**. Labels the path as absolute.

#### Path.setrelstr(_this_, _relativePathString_)
```c
void Path.setrelstr(PathObject* this, StringObject* relativePathString);
```
Sets this path to the **relativePathString**. Labels the path as relative.

#### Path.setabsstr(_this_, _absolutePathString_)
```c
void Path.setabsstr(PathObject* this, StringObject* absolutePathString);
```
Sets this path to the **absolutePathString**. Labels the path as absolute.

#### Path.dirname(_this_, _mem_)
```c
PathObject* Path.dirname(PathObject* this, MemoryObject* mem);
```
Returns the directory that **this** path resides in.

#### Path.basename(_this_)
```c
StringObject* Path.basename(PathObject* this);
```
Returns the last component of this path (i.e. the file or directory name).
