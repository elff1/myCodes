#include<stdio.h>

#define SN 8
#define MN 16
#define LN 32

long int cmul(short int a,short int b);
void cdiv(unsigned short int x, unsigned char y, unsigned short int *q, unsigned char *r);
void instruction(void);

int main(void){
	char Choice;
	short int a,b;
	unsigned short int x,q;
	unsigned char y,r;
	long int c;

	instruction();

	printf("\nChoice:");
	Choice=getchar();
	getchar();
	while(Choice!='0'){
		switch(Choice){
			case '5':
				printf("Input two 16-bit short ints:\n");
				scanf("%d%d",&a,&b);
				c=cmul(a,b);
				printf("%d * %d = %d\n",a,b,c);
				break;
			case '6':
				printf("Input a 16-bit unsigned short int and a 8-bit unsigned int:\n");
				scanf("%d%d",&x,&y);
				if(!y)
					printf("Divisor should be positive.\n");
				else{
					cdiv(x,y,&q,&r);
					printf("%d / %d = %d remains %d\n",x,y,q,r);
				}
				break;
			default:
				printf("Wrong choice number!\n\n");
				instruction();
		}

		printf("\nChoice:");
		do{
			Choice=getchar();
		}while(Choice>'9'||Choice<'0');
	}
}

long int cmul(short int a,short int b){
	int i,j,k,p,f;
	long int c;

	c=a;
	c&=(unsigned long)((1<<MN)-1);
	//printf("0x%X\t0x%X\t0x%X\n",c,b<<(MN),(-b)<<(MN));
	p=0;
	for(i=0;i<MN;i++){
		f=p-(unsigned long)c%2;
		//printf("%d:%d\t",i,f);
		if(f>0)
			c+=b<<(MN);
		else if(f<0)
			c+=(-b)<<(MN);
		p=(unsigned long)c%2;
		if(c&(1<<(LN-1))){
			c>>=1;
			c|=1<<(LN-1);
		}
		else
			c>>=1;
		//printf("0x%X\n",c);
	}

	return c;
}

void cdiv(unsigned short int x, unsigned char y, unsigned short int *q, unsigned char *r){
	unsigned long z,yy;
	int i;

	z=x;
	yy=y<<MN;
	//printf("0x%X\t0x%X\n",z,yy);
	for(i=0;i<MN;i++){
		z<<=1;
		if(z>=yy){
			z-=yy;
			z+=1;
		}
		//printf("%d:0x%X\n",i,z);
	}
	*q=z&((1<<MN)-1);
	*r=z>>MN;
}

void instruction(void){
	puts("Press 0, 5 or 6 to select an option:");
	puts("\t5: Multiply two short int x, y;");
	puts("\t6: Divide a unsigned short int by a 8-bit unsigned int;");
	puts("\t0:Quit.");
	//puts("Press \"Esc\" to quit.");
}