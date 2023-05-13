#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: symlink target linkpath\n");
        exit(1);
    }

    int error = symlink(argv[1], argv[2]);
    if (error) {
        printf("symlink: code is %d\n", error);
        exit(1);
    }

    return 0;
}