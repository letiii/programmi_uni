#include <stdio.h>
#include <stdlib.h>
#define BASE 10

int main(int argc, char * argv[]){
int num,k,out,i,aux,resto,cont=0;
/*si acquisiscono un valore naturale num e k cifre per sceglierne la dimensione */
do
	scanf("%d", &num);
while(num<=0);

do 
	scanf("%d",&k);
while(k<=0);
resto=num;
while(resto>0){
	resto=resto/10;
	cont++;
}
if(k<cont)
	printf("%d",num);
else{
out=0;
for(i=0;i<k;i++){
	out=out+(num%BASE);
	out=out*BASE;
	num=num/BASE;
}
out=out/BASE;
for(i=0;i<k;i++){
	aux=out%BASE;
	out=out/BASE;
	printf("%d",aux);

}}
printf("\n");
return 0;
}
