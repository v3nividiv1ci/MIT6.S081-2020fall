#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *file) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if (st.type != T_DIR) {
        fprintf(2, "find: second arg should be a directory\n");
        close(fd);
        return;
    }else {
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
            fprintf(2, "find: path too long\n");
            close(fd);
            return;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0){
                // 所以inum是什么，inum == 0又是什么情况？
                continue;
            }
            // 第一个参数是dest，第二个参数是source
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0) {
                fprintf(2, "find: cannot stat %s\n", buf);
                continue;
            }
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                continue;
            }
            if (st.type == T_DIR) {
                find(buf, file);
            }else if (st.type == T_FILE) {
                if (strcmp(de.name, file) == 0) {
                    fprintf(1, "%s\n", buf);
                }
            }
        }

    }


}

int main(int argc, char *argv[]) {
    find(argv[1], argv[2]);
    exit(0);
}