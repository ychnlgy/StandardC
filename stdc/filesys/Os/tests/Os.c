#include "stdc/unittest/print.h"

int main() {
    MemoryObject* mem = Memory.new();
    printBlue("cwd: ");
    printBold("%s\n", Os.cwd(mem));
    decref(mem);
}



