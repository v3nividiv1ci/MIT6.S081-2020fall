#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

char * strcat(char * dest, const char * src)
{
  char *tmp = dest;
 
  while (*dest)
    dest++;
  while ((*dest++ = *src++) != '\0')
    ;
  return tmp;
}


int main(int argc, char *argv[]) {
    char a;
    // 实现按行读取：一次读取一个字符直到出现\n
    char *buf = (char*)malloc(100*sizeof(char));

    char **args = (char**)malloc(MAXARG * sizeof(char*));
    for (int i = 1; i < argc; i ++) {
      args[i - 1] = argv[i];
      // fprintf(1, "args is %s, argv is %s\n", args[i - 1], argv[i]);
    }

    int n;
    int flag = 0, begin = 1;
          
    while((n = read(0, &a, sizeof(a))) > 0 ) {
      // fprintf(1, "%c", a);
        if (a != 'n' && flag == 1) {
          strcat(buf, "\\");
        }else if(a == '\\') {
          flag = 1;
        }else if((a == 'n' && flag == 1) || (a == '"' && begin != 1) || (a == '\n')) {
          args[argc - 1] = buf;
          if (fork() == 0) {
              exec(argv[1], args);
          }else {
              wait(0);
              for (int i = 1; i < argc; i ++) {
                args[i - 1] = argv[i];
              }
              memset(buf, 0, sizeof(buf));
              if (a == '\0' || a == '"') {
                free(buf);
                free(args);
                exit(0);
              }
              else {
                flag = 0;
              }
            }
        }else if (a != '"') {
            strcat(buf, &a);
        }else if (a == '"' && begin == 1) {
          begin = 0;
        }
    }

    exit(0);
}