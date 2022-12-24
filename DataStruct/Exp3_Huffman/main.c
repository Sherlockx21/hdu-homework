#include "huffman.h"

int main(int argc,char *argv[]){
    system("chcp 65001");

        Value_Encode("../file/hfmTree.txt","../file/TreeCodeFile.txt");
        File_Encode("../file/ToBeTran.txt","../file/CodeFile.txt");
        File_Decode("../file/CodeFile.txt","../file/CodePrint.txt");
        PrintTree("../file/TreePrint.txt");


	//LinkStack sp;
	//PushStack(&sp,'a');
	//printf("%c",sp->data);
}