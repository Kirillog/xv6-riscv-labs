#include "types.h"
#include "riscv.h"
#include "defs.h"

uint64 sys_get_lock(void) {
    return get_sleeplock();    
}

uint64 sys_acquire_lock(void) {
    int arg;
    argint(0, &arg);
    return acquire_sleeplock(arg);
}

uint64 sys_release_lock(void) {
    int arg;
    argint(0, &arg);
    return release_sleeplock(arg);
}

uint64 sys_delete_lock(void) {
    int arg;
    argint(0, &arg);
    return delete_sleeplock(arg);
}