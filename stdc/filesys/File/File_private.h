#ifndef STDC_FILESYS_FILE_PRIVATE
#define STDC_FILESYS_FILE_PRIVATE

#include "File_protected.h"

static Ptr new_File();
static void init_File(FileObject*);
static void del_File(Ptr);

static CStr cstr_File(FileObject*);
static bool equals_File(FileObject*, FileObject*);

static long size_File(FileObject*);

static void name_File(FileObject*, CStr);
static void namestr_File(FileObject*, StringObject*);
static void namepath_File(FileObject*, PathObject*);

static bool exists_File(FileObject*);
static bool readable_File(FileObject*);
static bool writable_File(FileObject*);

static void write_File(FileObject*, long, CStr);
static void writestr_File(FileObject*, StringObject*);
static FileData* read_File(FileObject*, MemoryObject*);
static long flush_File(FileObject*);
static ListObject* segment_File(FileObject*, MemoryObject*);

static bool remove_File(FileObject*);

#endif
