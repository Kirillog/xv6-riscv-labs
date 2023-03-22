#include "kernel/types.h"
#include "user.h"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Expected one argument\n");
        return -1;
    }
    int n;
    int pipe1[2], pipe2[2];
    if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
        printf("Pipe error\n");
        return -1;
    }
    int pid = fork();
    if (pid < 0) {
        printf("Fork error\n");
        return -1;
    }
    int lock = get_lock();
    if (lock < 0) {
        printf("Get lock error\n");
        return -1;
    }
    char c;
    if (pid != 0) {
        close(pipe1[0]);
        close(pipe2[1]);
        for (char *c = argv[1]; *c; ++c){
            write(pipe1[1], c, 1);
        }
        close(pipe1[1]);
        wait(0);
        while ((n = read(pipe2[0], &c, 1)) > 0) {
            acquire_lock(lock);
            printf("%d: received %c\n", getpid(), c);
            release_lock(lock);
        }
    } else {
        close(pipe2[0]);
        close(pipe1[1]);
        while ((n = read(pipe1[0], &c, 1)) > 0) {
            acquire_lock(lock);
            printf("%d: received %c\n", getpid(), c);
            release_lock(lock);
            write(pipe2[1], &c, 1);
        }
        close(pipe2[1]);
        delete_lock(lock);
    }
    return 0;
}
