#include<stdio.h>
#include "List.h"

void Print(struct List list){
	printf("(");
	Position pos=BeginPosition(list);
	if(pos!=EndPosition(list)){
		printf("%d",GetElem(list,pos));
		pos=NextPosition(list,pos);
	}
	while(pos!=EndPosition(list)){
		printf(",%d",GetElem(list,pos));
		pos=NextPosition(list,pos);
	}
	printf(")");
}

int main(){
	int i;
	struct List list=Create();
	Print(list);
	for(i=1;i<=5;i++){
		InsertBefore(&list,EndPosition(list),i);
	}
	Print(list);
	Position pos=LocateElem(list,3);
	if(pos!=EndPosition(list)){
		Delete(&list,pos);
	}
	InsertBefore(&list,BeginPosition(list),8);
	Print(list);
	Destroy(&list);
	return 0;
}
