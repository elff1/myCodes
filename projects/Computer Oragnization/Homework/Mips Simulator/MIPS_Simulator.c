#include<stdio.h>
#include<string.h>

#define insBase 0x10000				// the base address of the instruction; instruction will be stored in the front of the memory.
#define dataBase 800				// the base addrsss of data in the memory
#define MemCap 2000					// the capacity of the memory
#define BufSize 512

const char *insName[] = {
	"add",
	"sll",
	"bne",
	"lw",
	"addi",
	"j",
	0
};
const char *regName[] = {
	"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
	"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	"t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra", 0
};

typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned char byte;

void initialize();
void loadFile();
void run();
void display();

word pc, insNum;
byte mem[MemCap];
dword reg[32];

int main(){
	char choice[BufSize];
	initialize();
	loadFile();

	while((pc >> 2) < insNum){
		printf("\nInput \"n\" for the next instruction, \"q\" for quit:");
		gets_s(choice, BufSize);
		if(!strcmp(choice, "q"))
			break;
		if(strcmp(choice, "n")){
			printf("Wrong input. Try again.\n");
			continue;
		}
		run();
		display();
	}
	printf("\nEnd.\n");
}

void initialize(){
	int i;

	pc = 0;
	for(i = 0; i < 32; i++)
		reg[i] = 0;
}

void loadFile(){
	FILE *fp;
	word count = 0;
	int i;

	fp = fopen("code.txt", "rb");
	while(!feof(fp)){
		fread(&mem[count++], 1, 1, fp);
	}
	insNum = count >> 2;
	fclose(fp);

	/*for(i = 0; i < count; i++)
		printf("%X", mem[i]);
	printf("\n");*/
}

void run(){
	dword ins;
	dword opcode, rs, rt, rd, shamt, funct, imme, address;
	int i; 

	ins = 0;
	for(i = 0; i < 4; i++)
		ins = (ins << 8) + mem[pc + i];
	//printf("%X\n", ins);

	opcode = ins >> 26;
	rs = (ins >> 21) & 0x1f;
	rt = (ins >> 16) & 0x1f;
	rd = (ins >> 11) & 0x1f;
	shamt = (ins >> 6) & 0x1f;
	funct = ins & 0x3F;
	imme = ins & 0xffff;
	address = ins & 0x3ffffff;

	if(opcode == 0){
		switch(funct){
			case 0x20:
				reg[rd] = reg[rs] + reg[rt];
				break;

			case 0x00:
				reg[rd] = reg[rt] << shamt;
				break;
		}
		pc += 4;
	}else if(opcode < 4){
		switch(opcode){
			case 0x2:
				pc = (address << 2) - insBase;
				break;
		}
	}else{
		switch(opcode){
			case 0x5:
				if(reg[rs] != reg[rt])
					pc += (dword)imme;
				break;

			case 0x8:
				reg[rt] = reg[rs] + (dword)imme;
				break;

			case 0x23:
				reg[rt] = mem[reg[rs] + (dword)imme + dataBase];
				break;
		}
		pc += 4;
	}
}

void display(){
	int i;

	printf("PC:\t%X\n", pc);
	for(i = 0; i < 32; i++){
		printf("$%s:\t%X\t", regName[i], reg[i]);
		if(i % 4 == 3)
			printf("\n");
	}
}