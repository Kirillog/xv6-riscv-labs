#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"

struct multlock {
    struct sleeplock lock;
    int enabled;
};

struct multlock arr[NLOCK];
uint free_indexes[NLOCK];
uint ptr;
struct spinlock arr_lock; 

void lockarr_init() {
    ptr = 0;
    initlock(&arr_lock, "array lock");
    for (uint i = 0; i < NLOCK; i++) {
        free_indexes[i] = i;
        arr[i].enabled = 0;
        initsleeplock(&arr[i].lock, "");
    }
}

int get_sleeplock() {
    int id;
    acquire(&arr_lock);
    if (ptr < NLOCK) {
        id = free_indexes[ptr++];
        arr[id].enabled = 1;
    }
    else {
        id = -1;
    }
    release(&arr_lock);
    return id;
}


int acquire_sleeplock(uint id) {
    if (id >= NLOCK || !arr[id].enabled) {
        return -1;
    }
    acquiresleep(&arr[id].lock);
    return 0;
}

int release_sleeplock(uint id) {
    if (id >= NLOCK || !arr[id].enabled) {
        return -1;
    }
    releasesleep(&arr[id].lock);
    return 0;
}

int delete_sleeplock(uint id) {
    acquire(&arr_lock);   
    if (acquire_sleeplock(id) == -1) {
        return -1;
    }
    arr[id].enabled = 0;
    free_indexes[--ptr] = id;
    releasesleep(&arr[id].lock);
    release(&arr_lock);
    return 0;
}