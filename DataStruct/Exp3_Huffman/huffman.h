#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//头文件引入
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "union_H.h"
#include "text.h"
//树结构定义
//树结点定义
/**
 * 由于总结点数不会超过256*2-1，所以采用short型，两个字节十六位够用
 * 权值足够大，采用long型,八个字节
 */ 
typedef struct{
	unsigned char ch;//字符 0~255
	Weight_Type weight;//权值 
	short lchild,rchild,parent;//左孩子，右孩子，父节点下标值
	byte flag;//最小值被取标志
}TreeNode;


//编码类型定义
typedef struct{
	unsigned char ch;
	byte *encode;
	byte length;
}EncodeType;

//数定义
typedef struct{
	TreeNode *node;//树节点数组，数组下标范围0~510
	unsigned short length;//树节点总数，即树节点数组的大小，数组下标范围0~510
	unsigned short kindnum;//字符种数，范围0~256
	EncodeType *code;//编码存储数组
}HuffMan;

//函数运行状态声明
typedef enum{
	Create_File_OK,
	Create_File_FAIL,
	Node_FAIL,
	Decode_OK,
	Decode_FAIL,
	Encode_OK,
	Encode_FAIL,

}HuffMan_State;


//全局变量声明
//为了实现封装，未使用全局变量

//函数声明
HuffMan_State HuffMan_Encode(HuffMan *huffman);//根据哈夫曼树编码



HuffMan *Create_HuffManTree(unsigned long *ascii_dic,//ascii字典对应表
                            short array_length,//数组长度
							short kindnum//数量
	);//创建哈夫曼树
unsigned short Find_Min_Weight(HuffMan *huffman);//查找最小权值结点

HuffMan_State Create_HFFile(const char *str,HuffMan *huffman);//创建哈夫曼树文件str是路径

HuffMan_State Create_HFCodeFile(const char *str,HuffMan *huffman);//创建哈夫曼编码文件str是路径

void CodePrint(HuffMan *huffman);//编码类型打印

void FreeHuffman(HuffMan *huffman);//释放哈夫曼所有申请的内存空间

short Find_Code(HuffMan *huffman,char ch);//查找字符ch的在code中的位置

void File_Encode(const char *instr,const char *outstr);//根据路径instr文件编码，输出为outstr文件，创建名称为HFFile的哈夫曼树文件，创建名称为hfcode的编码文件

void Value_Encode(const char *HFFile,const char *HfCode);//根据输入的字符和权值编码

void File_Decode(const char *instr,const char *outstr);

void PrintAverageWe(HuffMan *huffman);

#endif