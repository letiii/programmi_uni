#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[]){
	int n1, n2,cont;
        scanf("%d %d",&n1,&n2);
	if(((n1%n2)==0)||((n2%n1)==0))
		cont=1;
	else
		cont=0;
	printf("%d\n",cont);
	return 0;
}
