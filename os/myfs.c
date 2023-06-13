#include "myfs.h"

int start_sys(){
  //fs_head 存储文件系统内容
  fs_head = (unsigned char *)malloc(DISK_SIZE);
  memset(fs_head,'\0',DISK_SIZE);

  FILE *fp;
  int i;

  if ((fp = fopen(PATH,"r")) != NULL){ //文件系统存在
    fread(fs_head,DISK_SIZE,1,fp); //读入文件
    fclose(fp);
  } else { //初始化文件系统
    printf("System initializing...\n");
    do_format();
    printf("System initialized finished.\n");
  }

  //拷贝根目录fcb至开启队列首部
  fcb_cpy(&openfile_list[0].open_fcb,((fcb*)(fs_head + 5*BLOCK_SIZE)));//分配5个盘块
  strcpy(openfile_list[0].dir,ROOT);//第一个目录设为根目录
  openfile_list[0].count = 0;
  openfile_list[0].state = 0;
  openfile_list[0].free = 1;
  curdir = 0;

  //利用空盘块填充开启队列
  fcb *empty = (fcb*)malloc(sizeof(fcb));
  set_fcb(empty,"\0",0,0,0,0);
  for (i = 1;i < MAX_OPENFILE;i++){
    fcb_cpy(&openfile_list[i].open_fcb,empty);
    strcpy(openfile_list[i].dir,"\0");
    openfile_list[i].free = 0;
    openfile_list[i].count = 0;
    openfile_list[i].status = 0;
  }

  //保存当前文件路径
  strcpy(current_dir,openfile_list[curdir].dir);
  start = ((block0*)fs_head)->start_block;//设置起始块号
  free(empty);
  return 0;
}

int my_format(char **args){
  unsigned char *ptr;
  FILE *fp;
  int i;

  //记录参数个数
  for(i = 0;args[i] != NULL;i++);
  if(i > 2){
    fprintf(stderr,"format:too much arguments to \"format\"\n");
    return 1;
  }


  if (args[1] != NULL){
    if(!strcmp(args[1],"-")){
      ptr = (unsigned char*)mallock(DISK_SIZE);
      memset(ptr,0,DISK_SIZE);
      fp = fopen(PATH,"w");
      fwrite(ptr,DISK_SIZE,1,fp);
      free(ptr);
      fclose(fp);
    }else{
      fprintf(stderr, "format:expected arguments to \"format\"\n" );
      return 1;
    }
  }
  do_format();
  return 1;
}

int do_format(void) {
    unsigned char *ptr = fs_head;
    int i;
    int first, second;
    FILE *fp;

    //初始盘块保存文件系统信息
    block0 *init_block = (block0 *) ptr;
    strcpy(init_block->information,"Disk Size = 1MB, Block Size = 1KB, Block0 in No.0, FAT0 and FAT1 in No.1 and No.3, Root Directory in No.5");
    init_block->root = 5;
    init_block->start_block = (unsigned char *) (init_block + BLOCK_SIZE * 7);
    ptr += BLOCK_SIZE;


    set_free(0, 0, 2);//保留块

    //分配盘块给FAT0，1
    set_free(get_free(1), 1, 0);
    set_free(get_free(2), 2, 0);
    set_free(get_free(2), 2, 0);

    ptr += BLOCK_SIZE * 4;

    fcb *root = (fcb *) ptr;
    first = get_free(ROOT_BLOCK_NUM);//第一个空闲盘块号
    set_free(first, ROOT_BLOCK_NUM, 0);
    set_fcb(root, ".", "di", 0, first, BLOCK_SIZE * 2, 1);
    root++;
    set_fcb(root, "..", "di", 0, first, BLOCK_SIZE * 2, 1);
    root++;

    for (i = 2; i < BLOCK_SIZE * 2 / sizeof(fcb); i++, root++) {
        root->free = 0;
    }

    memset(fs_head + BLOCK_SIZE * 7, 'a', 15);//第 7 个块的前 15 个字节设置为字母 'a'。

    //写入文件系统
    fp = fopen(PATH, "w");
    fwrite(fs_head, DISK_SIZE, 1, fp);
    fclose(fp);
}

int my_cd(char **args) {
    int i;
    int fd;
    char path[PATHLENGTH];
    fcb *dir;

    for (i = 0; args[i] != NULL; i++);
    if (i != 2) {
        fprintf(stderr, "cd: fail to parse arguments.\n");
        return 1;
    }

    memset(path, '\0', PATHLENGTH);
    get_abspath(path, args[1]);
    dir = find_fcb(path);
    if (dir == NULL || dir->attribute == 1) { //无目录或非目录
        fprintf(stderr, "cd: No such folder\n");
        return 1;
    }

    //查看文件是否在开启队列中
    for (i = 0; i < MAX_OPENFILE; i++) {
        if (openfile_list[i].free == 0) {
            continue;
        }

        if (!strcmp(dir->filename, openfile_list[i].open_fcb.filename) &&
            dir->first == openfile_list[i].open_fcb.first) {
            do_cd(i);
            return 1;
        }
    }

    if ((fd = do_open(path)) > 0) { //打开目录，保存文件描述符
        do_cd(fd);
    }

    return 1;
}

void do_cd(int fd) {
    curdir = fd;
    memset(current_dir, '\0', sizeof(current_dir));
    strcpy(current_dir, openfile_list[curdir].dir);
}

//打印文件路径
int my_pwd(char **args) {
    if (args[1] != NULL) {
        fprintf(stderr, "pwd: too many arguments\n");
        return 1;
    }

    printf("%s\n", current_dir);
    return 1;
}

int my_mkdir(char **args) {
    int i;
    char path[PATHLENGTH];
    char parpath[PATHLENGTH], dirname[NAMELENGTH];
    char *end;

    if (args[1] == NULL) {
        fprintf(stderr, "mkdir: missing operand\n");
        return 1;
    }

    for (i = 1; args[i] != NULL; i++) {
        //将文件路径拆成父子路径
        get_abspath(path, args[i]);
        end = strrchr(path, '/');
        if (end == path) {
            strcpy(parpath, "/");
            strcpy(dirname, path + 1);
        } else {
            strncpy(parpath, path, end - path);
            strcpy(dirname, end + 1);
        }

        if (find_fcb(parpath) == NULL) {//父目录不存在
            fprintf(stderr, "create: cannot create \'%s\': Parent folder not exists\n", parpath);
            continue;
        }
        if (find_fcb(path) != NULL) {//目录存在
            fprintf(stderr, "create: cannot create \'%s\': Folder or file exists\n", args[i]);
            continue;
        }

        do_mkdir(parpath, dirname);
    }

    return 1;
}

int do_mkdir(const char *parpath, const char *dirname) {
    int second = get_free(1); //获取空闲盘块
    int i, flag = 0, first = find_fcb(parpath)->first;//first为父目录磁盘块号
    fcb *dir = (fcb *) (fs_head + BLOCK_SIZE * first);

    //判断父目录是否有空闲fcb
    for (i = 0; i < BLOCK_SIZE / sizeof(fcb); i++, dir++) {
        if (dir->free == 0) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        fprintf(stderr, "mkdir: Cannot create more file in %s\n", parpath);
        return -1;
    }

    //没有空闲盘块
    if (second == -1) {
        fprintf(stderr, "mkdir: No more space\n");
        return -1;
    }
    set_free(second, 1, 0);

    set_fcb(dir, dirname, "di", 0, second, BLOCK_SIZE, 1);
    init_folder(first, second);
    return 0;
}

int my_rmdir(char **args) {
    int i, j;
    fcb *dir;

    if (args[1] == NULL) {
        fprintf(stderr, "rmdir: missing operand\n");
        return 1;
    }

    for (i = 1; args[i] != NULL; i++) {
        if (!strcmp(args[i], ".") || !strcmp(args[i], "..")) { //不可删除父目录
            fprintf(stderr, "rmdir: cannot remove %s: '.' or '..' is read only \n", args[i]);
            return 1;
        }

        if (!strcmp(args[i], "/")) { //不可删除根目录
            fprintf(stderr, "rmdir:  Permission denied\n");
            return 1;
        }

        dir = find_fcb(args[i]); //查找对应fcb
        if (dir == NULL) {
            fprintf(stderr, "rmdir: cannot remove %s: No such folder\n", args[i]);
            return 1;
        }

        if (dir->attribute == 1) {
            fprintf(stderr, "rmdir: cannot remove %s: Is a directory\n", args[i]);
            return 1;
        }

        for (j = 0; j < MAX_OPENFILE; j++) {
            if (openfile_list[j].free == 0) {
                continue;
            }

            if (!strcmp(dir->filename, openfile_list[j].open_fcb.filename) &&
                dir->first == openfile_list[j].open_fcb.first) {
                //目录处于打开状态
                fprintf(stderr, "rmdir: cannot remove %s: File is open\n", args[i]);
                return 1;
            }
        }

        do_rmdir(dir);
    }
    return 1;
}

void do_rmdir(fcb *dir) {
    int first = dir->first;

    dir->free = 0;//fcb标记为未使用
    dir = (fcb *) (fs_head + BLOCK_SIZE * first); //加入内存
    dir->free = 0; //标记为未使用
    dir++;
    dir->free = 0;

    set_free(first, 1, 1);
}

int my_ls(char **args) {
    int first = openfile_list[curdir].open_fcb.first; //当前盘块号
    int i, mode = 'n';
    int flag[3];
    fcb *dir;

    for (i = 0; args[i] != NULL; i++) {
        flag[i] = 0;
    }
    if (i > 3) {
        fprintf(stderr, "ls: failed parse arguments\n");
        return 1;
    }

    //判断指令格式
    flag[0] = 1;
    for (i = 1; args[i] != NULL; i++) {
        if (args[i][0] == '-') {
            flag[i] = 1;
            if (!strcmp(args[i], "-l")) {
                mode = 'l';
                break;
            } else {
                fprintf(stderr, "ls: wrong operand\n");
                return 1;
            }
        }
    }

    //判断类型
    for (i = 1; args[i] != NULL; i++) {
        if (flag[i] == 0) {
            dir = find_fcb(args[i]);
            if (dir != NULL && dir->attribute == 0) {
                first = dir->first;
            } else {
                fprintf(stderr, "ls: cannot access '%s': No such file or directory\n", args[i]);
                return 1;
            }
            break;
        }
    }

    do_ls(first, mode);

    return 1;
}

void do_ls(int first, char mode) {
    int i, count, length = BLOCK_SIZE;
    char fullname[NAMELENGTH], date[16], time[16];
    fcb *root = (fcb *) (fs_head + BLOCK_SIZE * first);
    block0 *init_block = (block0 *) fs_head;
    if (first == init_block->root) {
        length = ROOT_BLOCK_NUM * BLOCK_SIZE;
    }

    if (mode == 'n') {
        for (i = 0, count = 1; i < length / sizeof(fcb); i++, root++) {
            if (root->free == 0) {
                continue;
            }

            if (root->attribute == 0) {
                printf("%s", FOLDER_COLOR);
                printf("%s\t", root->filename);
                printf("%s", DEFAULT_COLOR);
            } else {
                get_fullname(fullname, root);
                printf("%s\t", fullname);
            }
            if (count % 5 == 0) {
                printf("\n");
            }
            count++;
        }
    } else if (mode == 'l') {
        for (i = 0, count = 1; i < length / sizeof(fcb); i++, root++) {
            /**< Check if the fcb is used. */
            if (root->free == 0) {
                continue;
            }

            trans_date(date, root->date);
            trans_time(time, root->time);
            get_fullname(fullname, root);
            printf("%d\t%6d\t%6ld\t%s\t%s\t", root->attribute, root->first, root->length, date, time);
            if (root->attribute == 0) {
                printf("%s", FOLDER_COLOR);
                printf("%s\n", fullname);
                printf("%s", DEFAULT_COLOR);
            } else {
                printf("%s\n", fullname);
            }
            count++;
        }
    }
    printf("\n");
}

int my_create(char **args) {
    int i;
    char path[PATHLENGTH];
    char parpath[PATHLENGTH], filename[NAMELENGTH];
    char *end;

    if (args[1] == NULL) {
        fprintf(stderr, "create: missing operand\n");
        return 1;
    }

    memset(parpath, '\0', PATHLENGTH);
    memset(filename, '\0', NAMELENGTH);

    for (i = 1; args[i] != NULL; i++) {
        get_abspath(path, args[i]);
        end = strrchr(path, '/');
        if (end == path) {
            strcpy(parpath, "/");
            strcpy(filename, path + 1);
        } else {
            strncpy(parpath, path, end - path);
            strcpy(filename, end + 1);
        }

        if (find_fcb(parpath) == NULL) {
            fprintf(stderr, "create: cannot create \'%s\': Parent folder not exists\n", parpath);
            continue;
        }
        if (find_fcb(path) != NULL) {
            fprintf(stderr, "create: cannot create \'%s\': Folder or file exists\n", args[i]);
            continue;
        }

        do_create(parpath, filename);
    }

    return 1;
}

int do_create(const char *parpath, const char *filename) {
    char fullname[NAMELENGTH], fname[16], exname[8];
    char *token;
    int first = get_free(1);
    int i, flag = 0;
    fcb *dir = (fcb *) (fs_head + BLOCK_SIZE * find_fcb(parpath)->first);

    /**< Check for free fcb. */
    for (i = 0; i < BLOCK_SIZE / sizeof(fcb); i++, dir++) {
        if (dir->free == 0) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        fprintf(stderr, "create: Cannot create more file in %s\n", parpath);
        return -1;
    }

    /**< Check for free space. */
    if (first == -1) {
        fprintf(stderr, "create: No more space\n");
        return -1;
    }
    set_free(first, 1, 0);

    /**< Split name and initial variables. */
    memset(fullname, '\0', NAMELENGTH);
    memset(fname, '\0', 8);
    memset(exname, '\0', 3);
    strcpy(fullname, filename);
    token = strtok(fullname, ".");
    strncpy(fname, token, 8);
    token = strtok(NULL, ".");
    if (token != NULL) {
        strncpy(exname, token, 3);
    } else {
        strncpy(exname, "d", 2);
    }

    /**< Set fcb. */
    set_fcb(dir, fname, exname, 1, first, 0, 1);

    return 0;
}

int my_rm(char **args) {
    int i, j;
    fcb *file;

    if (args[1] == NULL) {
        fprintf(stderr, "rm: missing operand\n");
        return 1;
    }

    for (i = 1; args[i] != NULL; i++) {
        file = find_fcb(args[i]);
        if (file == NULL) {
            fprintf(stderr, "rm: cannot remove %s: No such file\n", args[i]);
            return 1;
        }

        if (file->attribute == 0) {
            fprintf(stderr, "rm: cannot remove %s: Is a directory\n", args[i]);
            return 1;
        }

        for (j = 0; j < MAX_OPENFILE; j++) {
            if (openfile_list[j].free == 0) {
                continue;
            }

            if (!strcmp(file->filename, openfile_list[j].open_fcb.filename) &&
                file->first == openfile_list[j].open_fcb.first) {
                fprintf(stderr, "rm: cannot remove %s: File is open\n", args[i]);
                return 1;
            }
        }

        do_rm(file);
    }

    return 1;
}

void do_rm(fcb *file) {
    int first = file->first;

    file->free = 0;
    set_free(first, 0, 1);
}

int my_open(char **args) {
    int i, j;
    fcb *file;
    char path[PATHLENGTH];

    //-l打开所有文件
    if (args[1] == NULL) {
        fprintf(stderr, "open: missing operand\n");
        return 1;
    }
    if (args[1][0] == '-') {
        if (!strcmp(args[1], "-l")) {
            printf("fd filename exname state path\n");
            for (i = 0; i < MAX_OPENFILE; i++) {
                if (openfile_list[i].free == 0) {
                    continue;
                }

                printf("%2d %8s %-6s %-5d %s\n", i, openfile_list[i].open_fcb.filename,
                       openfile_list[i].open_fcb.exname,
                       openfile_list[i].fcb_state, openfile_list[i].dir);
            }
            return 1;
        } else {
            fprintf(stderr, "open: wrong argument\n");
            return 1;
        }
    }

    /**< Do open. */
    for (i = 1; args[i] != NULL; i++) {
        file = find_fcb(args[i]);
        if (file == NULL) {
            fprintf(stderr, "open: cannot open %s: No such file or folder\n", args[i]);
            return 1;
        }

        /**< Check if the file exist in openfile_list. */
        for (j = 0; j < MAX_OPENFILE; j++) {
            if (openfile_list[j].free == 0) {
                continue;
            }

            if (!strcmp(file->filename, openfile_list[j].open_fcb.filename) &&
                file->first == openfile_list[j].open_fcb.first) {
                /**< file is open. */
                fprintf(stderr, "open: cannot open %s: File or folder is open\n", args[i]);
                continue;
            }
        }

        do_open(get_abspath(path, args[i]));
    }
    return 1;
}


int do_open(char *path) {
    int fd = get_useropen();
    fcb *file = find_fcb(path);

    if (fd == -1) {
        fprintf(stderr, "open: cannot open file, no more useropen entry\n");
        return -1;
    }
    fcb_cpy(&openfile_list[fd].open_fcb, file);
    openfile_list[fd].free = 1;
    openfile_list[fd].count = 0;
    memset(openfile_list[fd].dir, '\0', 80);
    strcpy(openfile_list[fd].dir, path);

    return fd;
}

int my_close(char **args) {
    int i, j;
    fcb *file;

    //校验参数 -a删除所有文件，否则删除指定路径文件
    if (args[1] == NULL) {
        fprintf(stderr, "close: missing operand\n");
        return 1;
    }
    if (args[1][0] == '-') {
        if (!strcmp(args[1], "-a")) {
            for (i = 0; i < MAX_OPENFILE; i++) {
                if (i == curdir) {
                    continue;
                }
                openfile_list[i].free = 0;
            }
            return 1;
        } else {
            fprintf(stderr, "close: wrong argument\n");
            return 1;
        }
    }


    for (i = 1; args[i] != NULL; i++) {
        file = find_fcb(args[i]);//检查文件是否存在
        if (file == NULL) {
            fprintf(stderr, "close: cannot close %s: No such file or folder\n", args[i]);
            return 1;
        }
        //是否在开启列表中
        for (j = 0; j < MAX_OPENFILE; j++) {
            if (openfile_list[j].free == 0) {
                continue;
            }

            if (!strcmp(file->filename, openfile_list[j].open_fcb.filename) && file->first == openfile_list[j].open_fcb.first) {
                //文件打开，将其关闭
                do_close(j);
            }
        }
    }
    return 1;
}

void do_close(int fd) {
    if (openfile_list[fd].state == 1) { //文件被修改过
        fcb_cpy(find_fcb(openfile_list[fd].dir), &openfile_list[fd].open_fcb);//将内存中的文件控制块复制到磁盘中
    }
    openfile_list[fd].free = 0;//标记为可用状态
}

int my_write(char **args) {
    int i, j = 0, flag = 0;
    int mode = 'w';
    char c;
    char path[PATHLENGTH];
    char str[WRITE_SIZE];
    fcb *file;

    //校验参数
    for (i = 1; args[i] != NULL; i++) {
        if (args[i][0] == '-') {
            if (!strcmp(args[i], "-w")) {
                mode = 'w';
            } else if (!strcmp(args[i], "-c")) {
                mode = 'c';
            } else if (!strcmp(args[i], "-a")) {
                mode = 'a';
            } else {
                fprintf(stderr, "write: wrong argument\n");
                return 1;
            }
        } else {
            flag += 1 << i;
        }
    }
    if ((flag == 0) || (flag > 4) || i > 3) {
        fprintf(stderr, "write: wrong argument\n");
        return 1;
    }

    //检查文件类型
    strcpy(path, args[flag >> 1]);
    if ((file = find_fcb(path)) == NULL) {
        fprintf(stderr, "write: File not exists\n");
        return 1;
    }
    if (file->attribute == 0) {
        fprintf(stderr, "write: cannot access a folder\n");
        return 1;
    }

    memset(str, '\0', WRITE_SIZE);
    /**< Check if it's open. */
    for (i = 0; i < MAX_OPENFILE; i++) {
        if (openfile_list[i].free == 0) {
            continue;
        }

        if (!strcmp(file->filename, openfile_list[i].open_fcb.filename) && file->first == openfile_list[i].open_fcb.first) {
            if (mode == 'c') {
                printf("Please input location: ");
                scanf("%d", &openfile_list[i].count);
                getchar();
            }
            while (1) {
                for (; (str[j] = getchar()) != '\n'; j++);
                j++;
                if ((c = getchar()) == '\n') {
                    break;
                } else {
                    str[j] = c;
                    j++;
                }
            }

            if (mode == 'c') {
                do_write(i, str, j - 1, mode);
            } else {
                do_write(i, str, j + 1, mode);
            }

            return 1;
        }
    }

    fprintf(stderr, "write: file is not open\n");
    return 1;
}

int do_write(int fd, char *content, size_t len, int wstyle) {
    fat *fat1 = (fat *) (fs_head + BLOCK_SIZE);
    fat *fat2 = (fat *) (fs_head + 3*BLOCK_SIZE);

    //定义输入字符串数组，初始化
    char text[WRITE_SIZE] = {0};

    int write = openfile_list[fd].count;
    openfile_list[fd].count = 0;
    do_read(fd, openfile_list[fd].open_fcb.length, text);  //读取文件内容
    openfile_list[fd].count = write;

    int i = openfile_list[fd].open_fcb.first;

    char input[WRITE_SIZE] = {0};
    strncpy(input, content, len);
    if (wstyle == 'w') { //截断写，清空text，拷贝输入内容
        memset(text, 0, WRITE_SIZE);
        memcpy(text, input, len);
    } else if (wstyle == 'c') { //覆盖写，输入内容到指定位置
        memcpy(text + openfile_list[fd].count, input, len);
    } else if (wstyle == 'a') { //追加写，输入拷贝到text末尾
        memcpy(text + openfile_list[fd].count, input, len);
    }
    //写入文件系统
    int length = strlen(text); //需要写入的长度
    int num = length / BLOCK_SIZE + 1; //计算所需块数
    int static_num = num;

    while (num) { //循环写入内容
        char buf[BLOCK_SIZE] = {0};
        memcpy(buf, &text[(static_num - num) * BLOCK_SIZE], BLOCK_SIZE);
        unsigned char *p = fs_head + i * BLOCK_SIZE;
        memcpy(p, buf, BLOCK_SIZE);
        num = num - 1;
        if (num > 0) {// 是否还有下一次循环
            fat *fat_cur = fat1 + i;

            if (fat_cur->id == END) {//需要申请索引块
                int next = get_free(1);
                fat_cur->id = next;
                fat_cur = fat1 + next;
                fat_cur->id = END;
            }
            i = (fat1 + i)->id;
        }
    }
    //这时的i是刚写完的最后一个磁盘块，剩下的磁盘块可以free掉

    if (fat1[i].id != END) {
        int j = fat1[i].id;
        fat1[i].id = END;
        i = j;
        while (fat1[i].id != END) {
            int m = fat1[i].id;
            fat1[i].id = FREE;
            i = m;
        }
        fat1[i].id = FREE;
    }
    //更新后的 FAT 表拷贝到第四个块中，更新文件的长度和 FCB 状态，返回实际写入的字节数。
    memcpy(fat2, fat1, 2*BLOCK_SIZE);
    openfile_list[fd].open_fcb.length = length;
    openfile_list[fd].fcb_state = 1;
    return (strlen(input));
}

int my_read(char **args) {
    int i, flag = 0;
    int length;
    int mode = 'a';
    char path[PATHLENGTH];
    char str[WRITE_SIZE];
    fcb *file;
    //检验输入参数，仅-s和-a有效，-s选择读取文件的起始位置和读取的长度，-a表示读取整个文件
    for (i = 1; args[i] != NULL; i++) {
        if (args[i][0] == '-') {
            if (!strcmp(args[i], "-s")) {
                mode = 's';
            } else if (!strcmp(args[i], "-a")) {
                mode = 'a';
            } else {
                fprintf(stderr, "read: wrong argument\n");
                return 1;
            }
        } else {
            flag += 1 << i;
        }
    }
    if ((flag == 0) || (flag > 4) || i > 3) {
        fprintf(stderr, "read: wrong argument\n");
        return 1;
    }

    strcpy(path, args[flag >> 1]);
    if ((file = find_fcb(path)) == NULL) { //文件不存在
        fprintf(stderr, "read: File not exists\n");
        return 1;
    }
    if (file->attribute == 0) { //文件为文件夹
        fprintf(stderr, "read: cannot access a folder\n");
        return 1;
    }

    memset(str, '\0', WRITE_SIZE);
    for (i = 0; i < MAX_OPENFILE; i++) {
        if (openfile_list[i].free == 0) {
            continue;
        }

        if (!strcmp(file->filename, openfile_list[i].open_fcb.filename) && file->first == openfile_list[i].open_fcb.first) {
          //文件已经打开
            if (mode == 'a') {
                openfile_list[i].count = 0;
                length = UINT16_MAX;
            }
            if (mode == 's') {
                printf("Please input location: ");
                scanf("%d", &openfile_list[i].count);
                printf("Please input length: ");
                scanf("%d", &length);
                printf("-----------------------\n");
            }
            do_read(i, length, str);
            fputs(str, stdout);
            return 1;
        }
    }

    fprintf(stderr, "read: file is not open\n");
    return 1;
}
//从指定文件中读取指定长度的内容，返回实际读取的字符数
int do_read(int fd, int len, char *text) {  //text存储读取内容
    memset(text, '\0', BLOCK_SIZE * 20); //设置一次最大读取大小为20个盘块

    if (len <= 0){
        return 0;
    }

    fat *fat1 = (fat *) (fs_head + BLOCK_SIZE); //FAT1表
    int location = 0;//text的写入位置
    int length;
    int count = openfile_list[fd].count; //读写指针位置
    //排除了id出现end的情况
    if ((openfile_list[fd].open_fcb.length - count) >= len) { //可以读取的字符多于想要读取的字符
        length = len;  //想要读取的字符
    } else {
        length = openfile_list[fd].open_fcb.length - count; //只能读取这些字符
    }
    while (length){ //需要读取的字符串个数
        char *buf = (char *) malloc(BLOCK_SIZE); //申请空闲缓冲区
        int count = openfile_list[fd].count; //读写指针位置
        int logic_block_num = count / BLOCK_SIZE;//逻辑块号（起始为0）
        int off = count % BLOCK_SIZE;//块内偏移量
        int physics_block_num = openfile_list[fd].open_fcb.first;//文件起始物理块号（引导块号为0）

        for (int i = 0; i < logic_block_num; i++) { //物理块号
            physics_block_num = (fat1 + physics_block_num)->id; //FAT第一项为0，若为1则physics_block_num-1
        }
        unsigned char *p = fs_head + BLOCK_SIZE * physics_block_num; //该物理块起始地址
        memcpy(buf, p, BLOCK_SIZE);

        if ((off + length) <= BLOCK_SIZE) {//读取内容比剩余内容小，直接写入缓冲区
            memcpy(&text[location], &buf[off], length);
            openfile_list[fd].count = openfile_list[fd].count + length;
            location += length;  //下一次写的位置
            length = length - length;  //lenght = 0 将退出循环
        } else {
            memcpy(&text[location], &buf[off], BLOCK_SIZE - off); //将剩余内容读进text缓冲区
            //更新到下一个盘块位置，开始读取
            openfile_list[fd].count += BLOCK_SIZE - off;
            location += BLOCK_SIZE - off;
            length = length - BLOCK_SIZE - off; //还剩下的想要读取的字节数
        }
    }

    return location;
}

int my_exit_sys(void) {
    int i;
    FILE *fp;

    for (i = 0; i < MAX_OPENFILE; i++) {//关闭所有打开的文件
        do_close(i);
    }
    //写入状态到磁盘
    fp = fopen(PATH, "w");
    fwrite(fs_head, DISK_SIZE, 1, fp);
    free(fs_head);
    fclose(fp);
    return 0;
}
//查找空闲块
int get_free(int count) { //count为需要查找的空闲块个数
    unsigned char *ptr = fs_head;
    fat *fat0 = (fat *) (ptr + BLOCK_SIZE);
    int i, j, flag = 0;
    int fat[BLOCK_NUM];


    for (i = 0; i < BLOCK_NUM; i++, fat0++) {
        fat[i] = fat0->id;//将所有fat信息写入fat数组
    }
    //查找连续空闲块
    for (i = 0; i < BLOCK_NUM - count; i++) {
        for (j = i; j < i + count; j++) {
            if (fat[j] > 0) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            flag = 0;
            i = j;
        } else {//找到，返回第一个块编号
            return i;
        }
    }

    return -1;
}

int set_free(unsigned short first, unsigned short length, int mode) {
    fat *flag = (fat *) (fs_head + BLOCK_SIZE);
    fat *fat0 = (fat *) (fs_head + BLOCK_SIZE);
    fat *fat1 = (fat *) (fs_head + BLOCK_SIZE * 3);
    int i;
    int offset;

    for (i = 0; i < first; i++, fat0++, fat1++);

    if (mode == 1) {//释放空间
        while (fat0->id != END) {
            offset = fat0->id - (fat0 - flag) / sizeof(fat);
            fat0->id = FREE;
            fat1->id = FREE;
            fat0 += offset;
            fat1 += offset;
        }
        fat0->id = FREE;
        fat1->id = FREE;
    } else if (mode == 2) { //格式化fat
        for (i = 0; i < BLOCK_NUM; i++, fat0++, fat1++) {
            fat0->id = FREE;
            fat1->id = FREE;
        }
    } else {//分配空间
        for (; i < first + length - 1; i++, fat0++, fat1++) {
            fat0->id = first + 1;
            fat1->id = first + 1;
        }
        fat0->id = END;
        fat1->id = END;
    }

    return 0;
}

int set_fcb(fcb *f, const char *filename, const char *exname, unsigned char attr, unsigned short first,
            unsigned long length, char ffree) {
    time_t *now = (time_t *) malloc(sizeof(time_t));//获取当前时间戳
    struct tm *timeinfo;
    time(now);
    timeinfo = localtime(now);

    memset(f->filename, 0, 8);
    memset(f->exname, 0, 3);
    strncpy(f->filename, filename, 7);
    strncpy(f->exname, exname, 2);
    f->attribute = attr;
    f->time = get_time(timeinfo);
    f->date = get_date(timeinfo);
    f->first = first;
    f->length = length;
    f->free = ffree;

    free(now);
    return 0;
}

//转换时间结构体
unsigned short get_time(struct tm *timeinfo) {
    int hour, min, sec;
    unsigned short result;

    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    result = (hour << 11) + (min << 5) + (sec >> 1);

    return result;
}

//转换时间结构体
unsigned short get_date(struct tm *timeinfo) {
    int year, mon, day;
    unsigned short result;

    year = timeinfo->tm_year;
    mon = timeinfo->tm_mon;
    day = timeinfo->tm_mday;
    result = (year << 9) + (mon << 5) + day;

    return result;
}

fcb *fcb_cpy(fcb *dest, fcb *src) {
    memset(dest->filename, '\0', 8);
    memset(dest->exname, '\0', 3);

    strcpy(dest->filename, src->filename);
    strcpy(dest->exname, src->exname);
    dest->attribute = src->attribute;
    dest->time = src->time;
    dest->date = src->date;
    dest->first = src->first;
    dest->length = src->length;
    dest->free = src->free;

    return dest;
}

char *get_abspath(char *abspath, const char *relpath) {
    //是否是根目录或者以“/”开头
    if (!strcmp(relpath, DELIM) || relpath[0] == '/') {
        strcpy(abspath, relpath);
        return 0;
    }

    char str[PATHLENGTH];
    char *token, *end;

    memset(abspath, '\0', PATHLENGTH);
    abspath[0] = '/';
    strcpy(abspath, current_dir);

    strcpy(str, relpath);
    token = strtok(str, DELIM);

    do {
        if (!strcmp(token, ".")) {//路径为“.”直接跳过
            continue;
        }
        if (!strcmp(token, "..")) {//路径为“..”回上级目录
            if (!strcmp(abspath, ROOT)) { //已在根目录，直接跳过
                continue;
            } else {
                end = strrchr(abspath, '/');//到上一级目录末尾进行截断
                if (end == abspath) { //上一级为根目录，直接跳过
                    strcpy(abspath, ROOT);
                    continue;
                }
                memset(end, '\0', 1);
                continue;
            }
        }
        if (strcmp(abspath, "/")) { //非以上情况，加入路径末尾
            strcat(abspath, DELIM);
        }
        strcat(abspath, token);
    } while ((token = strtok(NULL, DELIM)) != NULL);

    return abspath;
}

fcb *find_fcb(const char *path) {
    char abspath[PATHLENGTH];
    get_abspath(abspath, path); //相对路径转为绝对路径
    char *token = strtok(abspath, DELIM);
    if (token == NULL) {//绝对路径为空，返回根目录fcb
        return (fcb *) (fs_head + BLOCK_SIZE * 5);
    }
    return find_fcb_r(token, 5);
}
//递归查找文件控制块
fcb *find_fcb_r(char *token, int first) { //param1:查找路径 param2: 起始块号
    int i, length = BLOCK_SIZE;
    char fullname[NAMELENGTH] = "\0";
    fcb *root = (fcb *) (BLOCK_SIZE * first + fs_head);//起始块号为first的第一个fcb
    fcb *dir;
    block0 *init_block = (block0 *) fs_head;
    if (first == init_block->root) { //是否是根目录
        length = ROOT_BLOCK_NUM * BLOCK_SIZE;
    }

    for (i = 0, dir = root; i < length / sizeof(fcb); i++, dir++) {
        if (dir->free == 0) { //pcb未占用
            continue;
        }
        get_fullname(fullname, dir);
        if (!strcmp(token, fullname)) {//找到文件fcb
            token = strtok(NULL, DELIM);
            if (token == NULL) {//到路径末尾
                return dir;
            }
            return find_fcb_r(token, dir->first);
        }
    }
    return NULL;
}

int get_useropen() {
    int i;
    //遍历数组，查找空闲表项
    for (i = 0; i < MAX_OPENFILE; i++) {
        if (openfile_list[i].free == 0) {
            return i;
        }
    }

    return -1;
}
//初始化文件夹
void init_folder(int first, int second) {
    int i;
    fcb *par = (fcb *) (fs_head + BLOCK_SIZE * first); //父级fcb
    fcb *cur = (fcb *) (fs_head + BLOCK_SIZE * second); //当前fcb

    set_fcb(cur, ".", "di", 0, second, BLOCK_SIZE, 1); //当前目录fcb设置
    cur++;
    set_fcb(cur, "..", "di", 0, first, par->length, 1); //父级目录fcb设置
    cur++;
    for (i = 2; i < BLOCK_SIZE / sizeof(fcb); i++, cur++) {//将剩余fcb字段设为0值
        cur->free = 0;
    }
}
//将文件名与拓展名组合
void get_fullname(char *fullname, fcb *fcb1) {
    memset(fullname, '\0', NAMELENGTH);

    strcat(fullname, fcb1->filename);
    if (fcb->attribute == 1) {//文件带拓展名，使用strncat防止字符缓冲区溢出
        strncat(fullname, ".", 2);
        strncat(fullname, fcb1->exname, 3);
    }
}
//将日期类型转化为字符串
char *trans_date(char *sdate, unsigned short date) {
    int year, month, day;
    memset(sdate, '\0', 16);

    year = date & 0xfe00;
    month = date & 0x01e0;
    day = date & 0x001f;
    sprintf(sdate, "%04d-%02d-%02d", (year >> 9) + 1900, (month >> 5) + 1, day);
    return sdate;
}
//将时间类型转化为字符串
char *trans_time(char *stime, unsigned short time) {
    int hour, min, sec;
    memset(stime, '\0', 16);

    hour = time & 0xfc1f;
    min = time & 0x03e0;
    sec = time & 0x001f;
    sprintf(stime, "%02d:%02d:%02d", hour >> 11, min >> 5, sec << 1);
    return stime;
}
