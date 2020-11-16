#include <stdio.h>
#include <stdlib.h>

void testStatic();

int main(int argc,char * argv[]){
	int val,i;
	scanf("%d",&val);
	for(i=0;i<val;i++)
		testStatic();
	return 0;
}


void testStatic(){
	static int cont=0;
	int num;
	num=0;
	cont++;
	num++;
	printf("variabile cont è %d e variabile num è %d\n",cont,num);
	return;
}