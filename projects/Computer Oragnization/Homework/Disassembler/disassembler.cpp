#include <stdio.h>

#define baseAddr 0x10000
#define LabelNumber 100
#define insNumber 200

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
typedef int insType[6];

int findLabel(dword *, int , dword);

int main(){
	dword code;
	insType ins[insNumber];
	dword label[LabelNumber];
	int insNum;
	int labNum;
	dword labAddr;	// the address of the label
	dword insAddr;	// the address of the currect instruction
	dword MaxLabAddr; // the maximum address of the instruction
	FILE *fi, *fo;
	int i, j, k;

	insNum = 0;
	labNum = 0;
	insAddr = baseAddr;
	MaxLabAddr = baseAddr;
	for(i = 0; i < insNumber; i++){
		ins[i][0] = -1;
		ins[i][1] = -1;
	}

	fi = fopen("code.txt", "rb");
	while(!feof(fi)){
		for(j = 3; j >= 0; j--)
			fread((char *)&code + j, 1, 1, fi);
		if(!feof(fi)){
			//printf("%x\n", code);
			
			ins[insNum][0] = 0;
			switch(code >> 26){
			case 0x00:
				switch(code & 0x3F){
				case 0:
					ins[insNum][1] = 1;
					break;
				case 0x20:
					ins[insNum][1] = 0;
					break;
				}
				break;
			case 0x5:
				ins[insNum][1] = 2;
				break;
			case 0x23:
				ins[insNum][1] = 3;
				break;
			case 0x8:
				ins[insNum][1] = 4;
				break;
			case 0x2:
				ins[insNum][1] = 5;
				break;
			}

			if(ins[insNum][1] < 2){
				ins[insNum][2] = (code >> 11) & 0x1f;
				ins[insNum][3] = (code >> 21) & 0x1f;
				ins[insNum][4] = (code >> 16) & 0x1f;
				ins[insNum][5] = (code >> 6) & 0x1f;
			}
			else if(ins[insNum][1] < 5){
				ins[insNum][2] = (code >> 16) & 0x1f;
				ins[insNum][3] = (code >> 21) & 0x1f;
				ins[insNum][4] = code & 0xffff;
				if(ins[insNum][1] < 3){
					labAddr = insAddr + ((ins[insNum][4] + 1) << 2);
					if(labAddr > MaxLabAddr)
						MaxLabAddr = labAddr;
					k = findLabel(label, labNum, labAddr);
					// if the label is not found, add it into the list
					if(k == labNum){
						label[k] = labAddr;
						labNum++;
						ins[(labAddr-baseAddr)>>2][0] = labNum;
					}
					ins[insNum][4] = k + 1;
				}
			}
			else{
				ins[insNum][2] = code & 0x3ffffff;
				labAddr = ((baseAddr >> 28) << 28) + (ins[insNum][2] << 2);
				if(labAddr > MaxLabAddr)
					MaxLabAddr = labAddr;
				k = findLabel(label, labNum, labAddr);
				// if the label is not found, add it into the list
				if(k == labNum){
					label[k] = labAddr;
					labNum++;
					ins[(labAddr-baseAddr)>>2][0] = labNum;
				}
				ins[insNum][2] = k + 1;
			}

			insNum++;
			insAddr += 4;
		}
	}
	fclose(fi);

	MaxLabAddr = ((MaxLabAddr - baseAddr) >> 2) + 1;
	insNum = (MaxLabAddr > insNum) ? MaxLabAddr : insNum;
	/*for(i = 0; i < insNum; i++){
		for(j = 0; j < 6; j++)
			printf("%X\t", ins[i][j]);
		printf("\n");
	}*/
	fo = fopen("mips.txt", "w");
	for(i = 0; i < insNum; i++){
		if(ins[i][0] < 0)
			continue;
		if(ins[i][0])
			fprintf(fo, "Label_%d:\n", ins[i][0]);
		if(ins[i][1] < 0)
			continue;
		fprintf(fo, "\t%s", insName[ins[i][1]]);
		if(ins[i][1] < 1){
			fprintf(fo, " $%s, $%s, $%s\n", regName[ins[i][2]], regName[ins[i][3]], regName[ins[i][4]]);
		}
		else if(ins[i][1] < 2){
			fprintf(fo, " $%s, $%s, %d\n", regName[ins[i][2]], regName[ins[i][4]], ins[i][5]);
		}
		else if(ins[i][1] < 3){
			fprintf(fo, " $%s, $%s, Label_%d\n", regName[ins[i][2]], regName[ins[i][3]], ins[i][4]);
		}
		else if(ins[i][1] < 4){
			fprintf(fo, " $%s, %d($%s)\n", regName[ins[i][2]], ins[i][4], regName[ins[i][3]]);
		}
		else if(ins[i][1] < 5){
			fprintf(fo, " $%s, $%s, %d\n", regName[ins[i][2]], regName[ins[i][3]], ins[i][4]);
		}
		else{
			fprintf(fo, " Label_%d\n", ins[i][2]);
		}
	}
}

int findLabel(dword *label, int labNum, dword labAddr){
	int i;

	for(i = 0; i < labNum; i++)
		if(label[i] == labAddr)
			return i;

	return i;
}