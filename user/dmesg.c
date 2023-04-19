#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

    if (argc != 1) {
        fprintf(2, "Usage: dmesg \n");
        exit(1);
    }

    if (dmesg() < 0) {
        fprintf(2, "dmesg: failed\n");
    }

    return 0;
}
