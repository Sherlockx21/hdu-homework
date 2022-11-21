#include <stdio.h>
#include <stdlib.h>
#include "union_H.h"

typedef unsigned long Text_Max;//文本字符串最大长度

//文本字符串结构定义
typedef struct{
	unsigned char *data;//文本字符串
	Text_Max length;//字符串长度
	unsigned short kindnum;//字符种数0~256
	Weight_Type char_ascii[Bytemax + 1];//ASCII码字符频率对应表,频率long型
}Text;

Text *CreateText(Text_Max length);//创建lenth长度的字符串文本

void ScanText(Text *text,byte mode);//扫描文本字符串，得到字符种数和ASCII吗字符频率

