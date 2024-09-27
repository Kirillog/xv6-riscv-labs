#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, const char* argv[]) {
    printf("vm print:\n");
    vmprint();
    printf("pgaccess entries:\n");
    pgaccess();
    printf("vm print:\n");
    vmprint();
    printf("pgaccess entries:\n");
    pgaccess();
    return 0;
}
