int main(int argc,char * argv[]){
	
	int n, dir;
	if(argc>1){
		n=atoi(argv[2]);
		dir=atoi(argv[3]);
		rot(argv[1],n,dir);
	}
	return 0;
}

void rot (char * voc, int n, int dir){
	char * aux;
	int vlen;
	
	if(aux=(char*)malloc(sizeof(char)*(vlen+1))){
		if(dir){
			memcpy(&aux[n],&voc[0],vlen-n);
			memcpy(&aux[0],&voc[vlen-n],n);
		}else{
			memcpy(&aux[0],&voc[n],vlen-n);
			memcpy(&aux[vlen-n],&voc[0],n);
		}
		aux[vlen]='\0';
		strcpy(voc,aux);
		free(aux);
	}else 
		printf("no memory\n");
}