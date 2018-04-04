# File

For simple parsing and writing bytes in files.

## Methods chart
| Interface | Method |
|-----------|--------|
| Object | ```Ptr File.new();``` |
|        | ```CStr File.cstr(FileObject* this);``` |
| File | ```void File.name(FileObject* this, CStr filename);``` |
|      | ```void File.namestr(FileObject* this, StringObject* filename);``` |
|      | ```void File.namepath(FileObject* this, PathObject* filename);``` |
|      | ```bool File.exists(FileObject* this);``` |
|      | ```bool File.readable(FileObject* this);``` |
|      | ```bool File.writable(FileObject* this);``` |
|      | ```void File.write(FileObject* this, long n, CStr data);``` |
|      | ```void File.writestr(FileObject* this, StringObject* data);``` |
|      | ```long File.flush(FileObject* this);``` |
|      | ```FileData* File.read(FileObject* this, MemoryObject* mem);``` |
|      | ```ListObject* File.segment(FileObject* this, MemoryObject* mem);``` |

## Files
 * [stdc/filesys/File/File.h](../stdc/filesys/File/File.h)
 * [stdc/filesys/File/protected.h](../stdc/filesys/File/protected.h)

## Demonstration
```c
#include "stdc/lib.h"

int main() {
  MemoryObject* mem = Memory.new();
  
  FileObject* f = Memory.make(mem, File.new);
  File.name(f, "foo.txt");
  
  File.write(f, 5, "Hello");
  File.write(f, 7, " world!");
  File.flush(f);
  
  FileData* fd = File.read(fd, mem);
  // fd->n == 12;
  // fd->d == "Hello world!"; // Note: no terminating null character!
  
  decref(mem);
}
```
## Struct
#### FileData
```c
typdef struct {
  long n; // number of bytes
  char* d; // data in bytes
} FileData;
```

## Object
#### File.new()
```c
Ptr File.new();
```
Returns pointer to new File.

#### File.cstr(_this_)
```c
CStr File.cstr(FileObject* this);
```
Returns the CStr representation of **this** file.

## File
#### File.name(_this_, _filename_)
```c
void File.name(FileObject* this, CStr filename);
```
Sets the name of **this** file to **filename**.

**Note that any data written but not flushed are not automatically flushed.**

#### File.namestr(_this_, _filename_)
```c
void File.namestr(FileObject* this, StringObject* filename);
```
Sets the name of **this** file to **filename**.

#### File.namepath(_this_, _filename_)
```c
void File.namestr(FileObject* this, PathObject* filename);
```
Sets the name of **this** file to **filename**.

#### File.exists(_this_)
```c
bool File.exists(FileObject* this);
```
Returns true if **this** file exists.

#### File.readable(_this_)
```c
bool File.readable(FileObject* this);
```
Returns true if **this** file has read permissions.

#### File.writable(_this_)
```c
bool File.writable(FileObject* this);
```
Returns true if **this** file has write permissions.

#### File.write(_this_, _n_, _data_)
```c
void File.write(FileObject* this, long n, CStr data);
```
Stores **n** bytes of **data** to the buffer of **this** file. **n** should be the length of **data**.

**Does not actually write to file. Remember to flush to write!**

#### File.writestr(_this_, _data_)
```c
void File.writestr(FileObject* this, StringObject* data);
```
Stores the StringObject **data** to the buffer of **this** file.

**Does not actually write to file. Remember to flush to write!**

#### File.flush(_this_)
```c
long File.flush(FileObject* this);
```
Writes all data on the buffer of **this** to the name of the file. 
Returns the number of bytes written. 
If the file does not exist or cannot be written, it returns ```-1```.

#### File.read(_this_, _mem_)
```c
FileData* File.read(FileObject* this, MemoryObject* mem);
```
Parses and returns all data in **this** file.
If the files does not exist or cannot be read, it returns ```NULL```.

#### File.segment(_this_, _mem_)
```c
ListObject* File.segment(FileObject* this, MemoryObject* mem);
```
Returns a list of FileData representing the bytes of **this** file segmented into a maximum size of 1 KB.
