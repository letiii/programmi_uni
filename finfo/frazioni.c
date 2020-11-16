#include <stdio.h>

typedef struct fra_s {
	int num, den;
}fra_t;
int main (int argc, char * argv[]){
	fra_t frazione;
	int i;
	scanf("%d %d",&frazione.num,&frazione.den);
	i=2;
	while(i<=frazione.num && i<=frazione.den)
		if(frazione.num%i==0&&frazione.den%i==0){
			frazione.num=frazione.num/i;
			frazione.den=frazione.den/i;
		}
		else
			i++;
	printf("%d / %d \n ",frazione.num,frazione.den);
	return 0;
}

