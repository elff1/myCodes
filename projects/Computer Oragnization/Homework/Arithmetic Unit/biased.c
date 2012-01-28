#include<stdio.h>
#include<string.h>

#define BITS 16

void instruction();
unsigned short int htod(char *);
unsigned short int dtob(int);
int btod(unsigned short int);
unsigned short int badd(unsigned short int,unsigned short int);
unsigned short int bsub(unsigned short int,unsigned short int);

int main(void){
	char Choice;
	int dx, dy;
	unsigned short int bx, by, bz;
	char str[100];

	instruction();

	printf("\nChoice:");
	Choice=getchar();
	getchar();
	while(Choice!='0'){
		switch(Choice){
			case '1':
				printf("A decimal number:");
				scanf("%d",&dx);
				getchar();
				printf("%d -> 0x%X\n",dx,dtob(dx));
				break;
			case '2':
				printf("A bianed number(in hexadecimal):");
				gets(str);
				bx=htod(str);
				printf("0x%X -> %d\n",bx,btod(bx));
				break;
			case '3':
				printf("Two 16-bit bianed numbers in two lines(in hexadecimal):\n");
				gets(str);
				bx=htod(str);
				gets(str);
				by=htod(str);
				bz=badd(bx,by);
				printf("0x%X + 0x%X = 0x%X\n",bx,by,bz);
				printf("%d + %d = %d\n",btod(bx),btod(by),btod(bz));
				break;
			case '4':
				printf("Two 16-bit bianed numbers in two lines(in hexadecimal):\n");
				gets(str);
				bx=htod(str);
				gets(str);
				by=htod(str);
				bz=bsub(bx,by);
				printf("0x%X - 0x%X = 0x%X\n",bx,by,bz);
				printf("%d - %d = %d\n",btod(bx),btod(by),btod(bz));
				break;
			default:
				printf("Wrong choice number!\n\n");
				instruction();
		}

		printf("\nChoice:");
		Choice=getchar();
		getchar();
	}
}

unsigned short int dtob(int dx){
	unsigned short int bx;

	bx=dx+(1<<(BITS-1));
	return bx;
}

int btod(unsigned short int bx){
	int dx;

	dx=bx-(1<<(BITS-1));
	return dx;
}

unsigned short int badd(unsigned short int bx,unsigned short int by){

	return bx+by-(1<<(BITS-1));
}

unsigned short int bsub(unsigned short int bx,unsigned short int by){

	return bx-by+(1<<(BITS-1));
}

unsigned short int htod(char *str){
	int i,len,dec;

	dec=0;
	len=strlen(str);
	for(i=len-1;i>=0;i--){
		if(str[i]<='9' && str[i]>='0')
			dec+=(str[i]-'0')<<(4*(len-i-1));
		else if(str[i]<='f' && str[i]>='a')
			dec+=(str[i]-'a'+10)<<(4*(len-i-1));
		else if(str[i]<='F' && str[i]>='A')
			dec+=(str[i]-'A'+10)<<(4*(len-i-1));
		else
			printf("Input number error!");
	}
	return dec;
}

void instruction(void){
	puts("Press 0-4 to select an option:");
	puts("\t1:Transform a decimal number into biased number;");
	puts("\t2:Transform a biased number into decimal number;");
	puts("\t3:Subtract a biased number by another;");
	puts("\t4:Sub;");
	puts("\t0:Quit.");
	//puts("Press \"Esc\" to quit.");
}