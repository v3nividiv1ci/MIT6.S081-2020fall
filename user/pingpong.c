#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define R 0
#define W 1
int main() {
    int p2c[2];
    int c2p[2];
    char buf = 'a';
    int pid;
    // int n;
    // create a pipe, with 2 FDs in fds[0], fds[1]
    pipe(p2c); 
    pipe(c2p);
    // create a child
    if (fork() == 0) {
        // close(p2c[W]);
        // close(c2p[R]);

        read(p2c[R], &buf, sizeof(char));
        pid = getpid();
        // fprintf(1, "%d: received ping\n", pid);
        printf("%d: received ping\n", pid);
        write(c2p[W], &buf, sizeof(char));
        // if (read(p2c[R], &buf, sizeof(char)) != sizeof(char)) {
        //     fprintf(2, "child read() error\n");
        // }else {
        //     pid = getpid();
        //     fprintf(1, "%d: received ping\n", pid);
        // }

        // if (write(c2p[W], &buf, sizeof(char)) != sizeof(char)) {
        //     fprintf(2, "child write() error\n");

        // }

        // sleep(10);
        // write(p2[0], &buf, sizeof(char));
        // close(p2c[R]);
        // close(c2p[W]);
        // exit(0);
    }else {
        // close fds[0];
        // parent send a byte to the child
        // close(p2c[R]);
        // close(c2p[W]);
        write(p2c[W], &buf, sizeof(char));
        read(c2p[R], &buf, sizeof(char));
        // fprintf(1, "%d: received pong\n", getpid());
        printf("%d: received pong\n", getpid());
        // if (write(p2c[W], &buf, sizeof(char)) != sizeof(char)) {
        //     fprintf(1, "parent write() error\n");
        // }

        // if (read(c2p[R], &buf, sizeof(char)) != sizeof(char)) {
        //     // pid = getpid();
        //     fprintf(1, "parent read() error\n");
        // }
        // fprintf(1, "%d: received pong\n", getpid());
        // sleep(10);

        // close(p2c[W]);
        // close(c2p[R]);
        // exit(0);
    }

    exit(0);
}