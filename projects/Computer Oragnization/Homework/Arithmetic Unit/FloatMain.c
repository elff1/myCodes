#include <stdio.h>
typedef unsigned long dword;

union{
float f;
dword k;
}u, v, z1, z2, z3, z4;

/*所有以下6个函数中，不能有任何float类型变量*/
dword atof(char*);
void ftoa(char*, dword);
dword fadd(dword, dword);
dword fsub(dword, dword);
dword fmul(dword, dword);
dword fdiv(dword, dword);
void printb(dword d);

int main(int argc, char *argv[])
{
char s[80], t[80];
dword m,i;

///*验证atof()与ftoa()*/
//scanf("%s", s);
//u.k = atof(s);
//ftoa(t, u.k);
//printf("%s\n%70.40f\n%s\n", s, u.f, t);

/*验证float + - * / */
scanf("%f", &u.f);
scanf("%f", &v.f);

//z1.k = fadd(u.k, v.k);
//z2.k = fsub(u.k, v.k);
//z3.k = fmul(u.k, v.k);
z4.k = fdiv(u.k, v.k);
//printf("add:\n%35.20f\n%35.20f\n\n", z1.f, u.f+v.f);
//printf("sub:\n%35.20f\n%35.20f\n\n", z2.f, u.f-v.f);
//printf("mul:\n%35.20f\n%35.20f\n\n", z3.f, u.f*v.f);
printf("div:\n%35.20f\n%35.20f\n\n", z4.f, u.f/v.f);

printb(u.k);
printb(v.k);
printb(z4.k);
z4.f=u.f/v.f;
printb(z4.k);

return 0;
}

void printb(dword d){
	dword m;
	int i;
	
	m=0x80000000; //u.d=0xFF800000;
	for(i=0; i<32; i++){
		if((i&7)==0)printf(" ");
		if(m&d)printf("1");
		else printf("0");
		m>>=1;
	}
	printf("\n");
}


dword fdiv(dword u, dword v){
	dword z,x,y,um,vm,zm;
	//unsigned long long x;
	unsigned char us,ue,vs,ve,zs,ze;
	int i;
	dword m;

	us=(u>>31);
	ue=(u>>23)&((1<<8)-1);
	um=u&((1<<23)-1)|(1<<23);
	vs=(v>>31);
	ve=(v>>23)&((1<<8)-1);
	vm=v&((1<<23)-1)|(1<<23);
	zs=us+vs;
	ze=(1<<7)-ve+ue-1;

	if(!v){
		if(!u){
			z=(256<<23)-1;
			return z;
		}
		if(us){
			z=1<<8;
			z=(z+255)<<23;
		}
		else
			z=255<<23;
		return z;
	}
	if(!u)
		return u;

	x=um;
	y=vm;
	zm=0;
	for(i=0;i<24;i++){
		zm<<=1;
		if(x>=y){
			x-=y;
			zm+=1;
		}
		x<<=1;
	}

	while(!(zm&(1<<23))){
		zm<<=1;
		ze--;
	}
	zm&=(1<<23)-1;

	z=zs;
	z=(z<<8)+ze;
	z=(z<<23)+zm;

	return z;
}