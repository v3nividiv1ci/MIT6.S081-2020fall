#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define R 0
#define W 1

void prime2(int *a2b) {
    int b2c[2];
    pipe(b2c);
    close(a2b[W]);
    // close(b2c[R]);
    int buf, n = 1;
    if (read(a2b[R], &buf, sizeof(int)) != 0) {
        n = buf;
        fprintf(1, "prime %d\n", buf);
    }
    while (read(a2b[R], &buf, sizeof(int)) != 0) {
        if (buf % n != 0) {
            // fprintf(1, "its %d\n", buf);
            write(b2c[W], &buf, sizeof(int));
        }
    }
    close(a2b[R]);

    if(fork() == 0) {
        prime2(b2c);
        exit(0);
    }else {
        // fprintf(1, "parent\n");
        close(b2c[W]);
        close(b2c[R]);
        wait(0);
        exit(0);
    }
}

int main() {
    int a2b[2];
    int buf;

    pipe(a2b);
    for (int i = 2; i <=35; i ++) {
        buf = i;
        write(a2b[W], &buf, sizeof(int));
    } 
    if (fork() == 0) {
        prime2(a2b);
        exit(0);
    }else {
        close(a2b[W]);
        close(a2b[R]);
        wait(0);
        exit(0);
        fprintf(1, "done");
    }
    return 0;
}
