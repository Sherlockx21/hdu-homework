#include "huffman.h"

HuffMan *myhuff;

//创建哈夫曼树
HuffMan *Create_HuffManTree(unsigned long *ascii_dic,//
						   short array_length,//
						   short kindnum){//创建哈夫曼树
	unsigned short i,j;//计次变量
	unsigned short min1,min2;//最小值
	HuffMan *huffman;//声明哈夫曼树指针
	huffman = (HuffMan *)malloc(sizeof(HuffMan));//分配空间
	huffman->length = 2 * kindnum - 1;//设置哈夫曼树的总结点树
	huffman->kindnum = kindnum;//设置哈夫曼树字符的种数
	huffman->node = (TreeNode *)malloc(sizeof(TreeNode)*huffman->length);//开辟总结数个树结点
	//初始化各结点各变量，并将ASCII数组中的下标转化 以及 权值赋值
	for(i = 0,j = 0;i < array_length;i++){
		if(ascii_dic[i]!=0){
			huffman->node[j].flag =0;
			huffman->node[j].lchild = -1;
			huffman->node[j].rchild = -1;
			huffman->node[j].parent = -1;
			huffman->node[j].ch = (char)(i);//将ASCII数组对应下标转化成字符
			huffman->node[j].weight = ascii_dic[i];//对应权值赋值
			j++;
		}
		if(i == Bytemax){//当最后一个字符统计完后，也就是最后一次循环结束前
			//初始化字符种数后的结点，以便于查找最小函数的使用
			for(;j < huffman->length;j++){
				huffman->node[j].flag=0;
				huffman->node[j].weight=0;
				huffman->node[j].lchild=-1;
				huffman->node[j].rchild=-1;
				huffman->node[j].parent=-1;
			}
		}
	}
	
	//将各个树结点链接起来，构建哈夫曼树
	for(i = huffman->kindnum;i < huffman->length;i++){
		min1=Find_Min_Weight(huffman);
		min2=Find_Min_Weight(huffman);
		huffman->node[i].weight = huffman->node[min1].weight+huffman->node[min2].weight;
		huffman->node[min1].parent = i;
		huffman->node[min2].parent = i;
		huffman->node[i].lchild = min1;
		huffman->node[i].rchild = min2;
	}
	//返回huffman指针
	return huffman;
}

unsigned short Find_Min_Weight(HuffMan *huffman){//查找最小权值结点位置
	unsigned short i;//计次变量
	unsigned long temp;//临时变量，存放最小值
	unsigned short locate;//位置变量，最放最小值的位置

	//扫描结点的权值，将第一个未被取出的权值赋值给temp，以及位置赋值给locate
	for(i = 0;i < huffman->length;i++){
		if(huffman->node[i].flag == 0 && huffman->node[i].weight != 0){
			temp = huffman->node[i].weight;
			locate = i;
			break;
		}
	}
	//扫描结点的权值，找到未被取出的权值中的最小权值
	for(i = 0;i < huffman->length;i++){
		if(huffman->node[i].weight != 0 && huffman->node[i].flag == 0 && temp > huffman->node[i].weight){
			temp = huffman->node[i].weight;
			locate = i;
		}
	}
	//设置已被取出标志
	huffman->node[locate].flag=1;
	return locate;
}

HuffMan_State Create_HFFile(const char *str,HuffMan *huffman){
	unsigned short i;
	FILE *fp = fopen(str,"wt+");//创建文件
	if(fp == NULL){
		return Create_File_FAIL;//创建失败
	}
	for(i = 0;i < huffman->length;i++){
		fprintf(fp,"id:%d ch:%c weight:%ld ",i,huffman->node[i].ch,huffman->node[i].weight);
		fprintf(fp,"parent:%d lchild:%d rchild:%d\n",huffman->node[i].parent,huffman->node[i].lchild,huffman->node[i].rchild);
	}
	fclose(fp);
	return Create_File_OK;//创建成功
}

HuffMan_State HuffMan_Encode(HuffMan *huffman){
	Stack *sq = CreateStack();//初始化栈
	unsigned short i;//对应下标志，范围在0~510，所以用short类型
	short current;//当前节点位置
	byte p;
	byte e;
	huffman->code = (EncodeType *)malloc(sizeof(EncodeType)*huffman->kindnum);
	for(i = 0;i < huffman->kindnum;i++){
		for(current = i,p = 0;huffman->node[current].parent != -1;current = huffman->node[current].parent){
			if(huffman->node[huffman->node[current].parent].lchild == current){//左子节点
				PushStack(sq,'0');
				p++;
			}else{//右子节点
				PushStack(sq,'1');
				p++;
			}
		}
		//给编码字符赋值
		huffman->code[i].ch = huffman->node[i].ch;
		//开辟相应个节点的空间大小
		huffman->code[i].length = p;
		huffman->code[i].encode = (byte *)malloc(sizeof(byte)*p);
		//所有元素出栈
		p = 0;
		while(!StackIsEmpty(sq)){//当栈不空
            e = StackGetTop(sq);
			PopStack(sq);
			sprintf(&huffman->code[i].encode[p++],"%c",e);
		}
		//printf("%s\n",huffman->code[i].decode);
	}
	return Encode_OK;
}
//打印字符编码
void CodePrint(HuffMan *huffman){
	short i;
	for(i = 0;i < huffman->kindnum;i++){
		printf("char_id:%d char:%c,code:%s\n",huffman->code[i].ch,huffman->code[i].ch,huffman->code[i].encode);
	}
}
//创建哈夫曼编码文件
HuffMan_State Create_HFCodeFile(const char *str,HuffMan *huffman){
	FILE *fp = fopen(str,"wt+");//打开或创建可读可写文件
	short i;
	if(fp == NULL) return Create_File_FAIL;
	for(i = 0;i < huffman->kindnum;i++){
		fprintf(fp,"%c:%s\n",huffman->code[i].ch,huffman->code[i].encode);
	}
	fclose(fp);
	return Create_File_OK;
}

void FreeHuffman(HuffMan *huffman){
	free(huffman->node);
	free(huffman->code);
	free(huffman);
}




//实现题目所给要求，即将所需函数用逻辑拼接起来

void Value_Encode(const char *HFFile,const char *HFCode){
	unsigned short kindnum;//字符种类数
    unsigned short i;//计数
    unsigned long ascii[256];//ASCII对应表
    unsigned char *ascii_char;//ASCII字符对应表
	//FILE *out;//输出文件
	//char ch;//临时字符
	HuffMan *huffman;//哈夫曼树
	//out=fopen(outstr,"wt+");//打开out文件
	printf("请输入字符种类数：");
    scanf("%hd",&kindnum);//输入
    getchar();//吸收回车
    ascii_char = (unsigned char *)malloc(sizeof(unsigned char)*kindnum);//开辟字符类数字符数组
	printf("请输入字符（以空格为间隔）:");
    for(i = 0;i < kindnum;i++){
        scanf("%c",&ascii_char[i]);
        getchar();//吸收回车
    }
	for(i = 0;i < 256;i++) ascii[i]=0;
	printf("请输入各字符权值（与上方对应）:");
    for(i = 0;i < kindnum;i++){
        scanf("%ld",&ascii[(int)ascii_char[i]]);
    }
	huffman = Create_HuffManTree(ascii,256,kindnum);//创建哈夫曼树
    myhuff = huffman;
	Create_HFFile(HFFile,huffman);//创建哈夫曼树文件
	HuffMan_Encode(huffman);//哈夫曼编码
	//CodePrint(huffman);
	CodePrint(huffman);
	//PrintAverageWe(huffman);
	Create_HFCodeFile(HFCode,huffman);//哈夫曼编码文件
	//i=0;
	//while(i<kindnum){
		//fscanf(fp,"%c",&ch);
	//	fprintf(out,"%s",huffman->code[Find_Code(huffman,ascii_char[i])].decode);
	//	i++;
	//}
	//fclose(out);
	//FreeHuffman(huffman);
}

//void File_Encode(const char *instr,const char *outstr,const char *HFFile,const char *HFCode)
void File_Encode(const char *instr,const char *outstr){
	FILE *fp;//输入文件
	FILE *out;//输出文件


	unsigned char ch;

	fp = fopen(instr,"r");//只读方式打开输入文件
	out = fopen(outstr,"wt+");//可写创建或打开输出文件
	//开始统计文本长度已经字符频率
//	while((ch = fgetc(fp)) != 255){//文本未结束
//		//fscanf(fp,"%c",&ch);
//		text->char_ascii[(int)ch]++;
//		text->length++;
//	}
	//fclose(fp);//后面用不到，及时关闭，节省内存
//	//统计字符种类
//	ScanText(text,0);
//	//创建哈夫曼树
//	huffman = Create_HuffManTree(text->char_ascii,256,text->kindnum);
//	//哈夫曼树写入文件hffile
//	Create_HFFile(HFFile,huffman);
//	//根据生成的哈夫曼树进行编码
//	HuffMan_Encode(huffman);
//	//打印编码文件
//	CodePrint(huffman);
//	//将编码写入文件hfcode
//	Create_HFCodeFile(HFCode,huffman);
//	PrintAverageWe(huffman);
//	//fp指向文件头
//	rewind(fp);
	//对输入文件进行编码，写入输出文件
	while((ch = fgetc(fp)) != EOF){
		//fscanf(fp,"%c",&ch);
        printf("%s",myhuff->code[Find_Code(myhuff,ch)].encode);
		//fprintf(out,"%s",myhuff->code[Find_Code(myhuff,ch)].encode);
	}
    fclose(fp);
	//关闭out文件流
	fclose(out);
//	//释放huffman所有申请内存
//	FreeHuffman(huffman);
}


void File_Decode(const char *instr,const char *outstr){
    FILE *fp;//输入文件
    FILE *out;//输出文件
    Text *text;//声明文本
    unsigned char ch;
    text = CreateText(0);//创建文本
    fp = fopen(instr,"r");//只读方式打开输入文件
    out = fopen(outstr,"wt+");//可写创建或打开输出文件
    //fclose(fp);//后面用不到，及时关闭，节省内存
    //HuffMan_Decode(text,myhuff);
    int node,root;
    for(int i = 0;i < myhuff->kindnum;i++){ //找到根
        if(myhuff->node[i].parent == -1){
            root = i;
            node = i;
            break;
        }
    }
    while((ch = fgetc(fp)) != EOF){
        if(ch == '0') node = myhuff->node[node].lchild;
        if(ch == '1') node = myhuff->node[node].rchild;
        if(myhuff->node[node].lchild == -1 && myhuff->node[node].rchild == -1){
            printf("%c",myhuff->node[node].ch);
            //fprintf(out,"%c",myhuff->node[node].ch);
            node = root;
        }
    }
    //关闭out文件流
    fclose(out);
    //fclose(fp);
    //释放huffman所有申请内存
    //FreeHuffman(myhuff);
}

short Find_Code(HuffMan *huffman,char ch){
	short i;
	for(i = 0;i < huffman->kindnum;i++){
		if(ch == huffman->code[i].ch)
			return i;
	}
}

void PrintAverageWe(HuffMan *huffman){
	long sum = 0;
	int i;
	long m = 0;
	for(i = 0;i < huffman->kindnum;i++){
		/* code */
		m += huffman->node[i].weight;
	}
	for(i = 0;i < huffman->kindnum;i++){
		//printf("(%d/%d)*%d",huffman->node[i].weight,m,huffman->code[i].lenth);
		sum += huffman->node[i].weight*huffman->code[i].length;
	}
	printf("平均码长为：%lf",sum/1.0/m);
}