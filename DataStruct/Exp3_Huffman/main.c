#include "huffman.h"

int main(int argc,char *argv[]){
    system("chcp 65001");
	byte option;
	while(1){
		printf("请输入您的选择：");
		scanf("%d",&option);
		switch(option){
			case 1:
				Value_Decode("../file/hfmTree.txt","../file/CodeFile.txt");
				break;
			case 2:
				File_Decode("../file/ToBeTran.txt","../file/CodePrint.txt","../file/htmTree.txt","../file/CodeFile.txt");
				break;
		}
	}
	//LinkStack sp;
	//PushStack(&sp,'a');
	//printf("%c",sp->data);
}