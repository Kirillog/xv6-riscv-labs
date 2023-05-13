#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[MAXPATH];

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: readlink linkpath\n");
        exit(1);
    }

    int error = readlink(argv[1], buf);
    if (error) {
        printf("readlink: code is %d\n", error);
        exit(1);
    }

    printf("%s\n", buf);
    return 0;
}