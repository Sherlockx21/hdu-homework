#include "text.h"

Text *CreateText(unsigned long length){
	Text *text;//声明text指针
	short i;//计数变量
	text = (Text *)malloc(sizeof(Text));//分配空间
	text->length = length;//设置文本字符串长度
	text->data = (unsigned char *)malloc(sizeof(unsigned char)*text->length);//开辟文本字符串长度个字符数组
	text->kindnum=0;//种类初始化为0
	for(i = 0;i <= Bytemax;i++){//ASCII码表初始化
		text->char_ascii[i]=0;
	}
	return text;
}

void ScanText(Text *text,byte mode){
	Text_Max i;
	/**
	 * 扫描字符串，
	 * 得到ASCII码字符频率表
	 */
	if(mode==1){
		for(i=0;i < text->length;i++){
			text->char_ascii[(int)(text->data[i])]++;
		}
	}
	/**
	 * 扫描字ASCII码表
	 * 统计出现的字符种类数
	 */
	for(i = 0;i <= Bytemax;i++){
		if(text->char_ascii[i] != 0){
			text->kindnum++;
		}
	}
}

void PrintText(Text *text){
	short i;
	for(i = 0;i <= Bytemax;i++){
		printf("%ld ",text->char_ascii[i]);
		if(i % 15 == 0 && i != 0) printf("\n");
    }
}