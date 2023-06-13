#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#ifndef MY_FS_H
#define MY_FS_H
//定义全局变量
#define BLOCK_SIZE 1024 //盘块大小
#define BLOCK_NUM 1024 //盘块数
#define DISK_SIZE 1048576 //磁盘大小
#define PATH "/home/exp/exp5/fs" //映射路径
#define END 0xffff  //文件块末尾
#define FREE 0x0000 //未占用空间
#define ROOT "/" //根目录名称
#define ROOT_BLOCK_NUM 2 //根目录块数
#define MAX_OPENFILE 10 //最大打开文件数
#define NAMELENGTH 32 //文件名长度
#define PATHLENGTH 128 //路径长度
#define DELIM "/"//分隔符
#define WRITE_SIZE 20 * BLOCK_SIZE
//文件系统第一个物理块
typedef struct BLOCK0 {
    char information[200]; //基本信息
    unsigned short root;  //根目录第一个物理块号
    unsigned char *start_block; //空闲块链表起始地址
} block0;

typedef struct FCB{
  char filename[8]; //文件名
  char exname[3]; //文件拓展名
  unsigned char attribute; //是否有拓展名
  unsigned char reserve[10]; //保留字段
  unsigned short time; //创建时间
  unsigned short date; //创建日期
  unsigned short first; //第一个文件块号
  unsigned short length; //文件块个数
  char free; //标志位
} fcb;

typedef struct USEROPEN{
  fcb open_fcb; //打开文件的pcb
  char dir[80]; //当前路径
  int count; //文件读写指针位置
  char state; //文件状态
  char free; //标志位
} useropen;

unsigned char *fs_head; //头文件
useropen openfile_list[MAX_OPENFILE]; //文件开启目录
int curdir; //当前文件编号
char current_dir[80]; //当前文件目录
unsigned char *start; //第一个有数据的盘块

//functions
int start_sys();
int my_format(char **args);
int do_format();
int my_cd(char **args);
void do_cd(int fd);
int my_pwd(char **args);
int my_mkdir(char **args);
void do_mkdir(const char *parpath,const char *dirname);
int my_rmdir(char **args);
void do_rmdir(fcb *dir);
int my_ls(char **args);
void do_ls(int first,char mode);
int my_create(char **args);
int do_create(const char *parpath, const char *filename);
int my_rm(char **args);
void do_rm(fcb *file);
int my_open(char **args);
int do_open(char *path);
int my_close(char **args);
void do_close(int fd);
int my_write(char **args);
int do_write(int fd, char *content, size_t len, int wstyle);
int my_read(char **args);
int do_read(int fd, int len, char *text);
int my_exit_sys();
int get_free(int count);
int set_free(unsigned short first, unsigned short length, int mode);
int set_fcb(fcb *f, const char *filename, const char *exname, unsigned char attr, unsigned short first,unsigned long length,char ffree);
unsigned short get_time(struct tm *timeinfo);
unsigned short get_date(struct tm *timeinfo);
fcb * fcb_cpy(fcb *dest, fcb *src);
char * get_abspath(char *abspath, const char *relpath);
int get_useropen();
fcb *find_fcb(const char *path);
fcb *find_fcb_r(char *token, int root);
void init_folder(int first, int second);
void get_fullname(char *fullname, fcb *fcb1);
char *trans_date(char *sdate, unsigned short date);
char *trans_time(char *stime, unsigned short time);

#endif
