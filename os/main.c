#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "myfs.h"


//指令列表
char *builtin_str[] = {
        "format",
        "cd",
        "mkdir",
        "rmdir",
        "ls",
        "create",
        "rm",
        "write",
        "read",
        "exit",
        "open",
        "close",
        "pwd"
};
//将函数内置入文件系统
int (*builtin_func[])(char **) = {
        &my_format,
        &my_cd,
        &my_mkdir,
        &my_rmdir,
        &my_ls,
        &my_create,
        &my_rm,
        &my_write,
        &my_read,
        &my_exit_sys,
        &my_open,
        &my_close,
        &my_pwd
};

//指令个数
int builtins_num() {
    return sizeof(builtin_str) / sizeof(char*);
}


int sh_launch(char **args){
    pid_t pid, wpid;
    int status;//子进程状态

    pid = fork();//创建子进程
    if (pid == 0) {//子进程
      //int execvp(const char *file, char *const argv[]);（文件名，命令行参数） 当前进程中启动一个新的进程，并替换当前进程的代码和数据段，从而运行新的程序
        if (execvp(args[0], args) == -1) { //执行指定的命令及其参数
            perror("sh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {//创建失败
        perror("sh");
    } else {//父进程
        do {
            wpid = waitpid(pid, &status, WUNTRACED);//挂起进程
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); //子进程正常退出或信号退出
    }

    return 1;
}


int sh_execute(char **args){
    int i;
    if (args[0] == NULL) {//空命令
        return 1;
    }

    //查看命令是否存在
    for (i = 0; i < builtins_num(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);//类型转化
        }
    }

    return sh_launch(args);
}

//按行读入数据
char *sh_read_line(void) {
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\r\n\a"

char **sh_split_line(char *line) {
    int bufsize = SH_TOK_BUFSIZE, position = 0;//bufsize存储输入行大小，position存储单词位置
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {//内存不足，无法分配
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SH_TOK_DELIM);
    while (token != NULL) {
      //存储单词
        tokens[position] = token;
        position++;
        //扩容
        if (position >= bufsize) {
            bufsize += SH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "sh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// 循环读指令
void sh_loop(void){
    char *line;
    char **args;
    int status;

    do {
        printf("\n\e[1mleslie\e[0m@leslie-PC \e[1m%s\e[0m\n", current_dir);//打印命令提示符，包含当前用户名和计算机名称，以及当前工作目录的路径
        printf("> \e[032m$\e[0m ");
        line = sh_read_line();
        args = sh_split_line(line);
        status = sh_execute(args);

        free(line);
        free(args);
    } while (status);
}


int main(int argc, char **argv)
{
    start_sys();
    sh_loop();

    return EXIT_SUCCESS;
}
