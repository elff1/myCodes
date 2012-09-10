#include <stdio.h>
#include <string.h>
#include <math.h>
#include "encode.h"
#include "globals.h"

unsigned int ELFHash(const char *str, unsigned int len) {
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;
	for (i = 0; i < len; str++, i++) {
		hash = (hash << 4) + (*str);
		if ((x = hash & 0xF0000000L) != 0) {
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash;
}

void output(const char *str) {
	fprintf(fout, "%s\n", str);
}

static int funcIsMain(int funcName) {
	if(funcName == ELFHash("main", 4))
		return 1;
	return 0;
}

static void getVarStr(char *varStr, int offset) {
	if(offset >= 0)
		sprintf(varStr, "[%s+%d]", EBP, offset);
	else
		sprintf(varStr, "[%s%d]", EBP, offset);
}

static int getRegStr(char *regStr, int reg) {
	switch(reg) {
	case 1:
		strcpy(regStr, EAX);
		return 0;
	case 2:
		strcpy(regStr, EBX);
		return 0;
	case 3:
		strcpy(regStr, ECX);
		return 0;
	case 4:
		strcpy(regStr, EDX);
		return 0;
	}
	return -1;
}

int creatLabel() {
	static int labelNo = 0;
	return ++labelNo;
}

void codeLabel(int labelNo) {
	sprintf(strBucket, "%s%d:", LABEL, labelNo);
	output(strBucket);
}

void codeJmp(int labelNo) {
	sprintf(strBucket, "%s\t%s%d", JMP, LABEL, labelNo);
	output(strBucket);
}

void codePop(int reg) {
	char regStr[REGSTR_LENGTH];
	getRegStr(regStr, reg);

	sprintf(strBucket, "%s\t%s", POP, regStr);
	output(strBucket);
}

void codeLeaGlobal(int target, int addr, int offset) {
	int array;

	char offReg[REGSTR_LENGTH];
	char tarReg[REGSTR_LENGTH];
	array = getRegStr(offReg, offset);
	getRegStr(tarReg, target);

	if(array == -1) {
		sprintf(strBucket, "%s\t%s, [%s%d]", LEA, tarReg, GDATA_PRE, addr);
	} else {
		sprintf(strBucket, "%s\t%s, [%s%d+%s]", LEA, tarReg, GDATA_PRE, addr, offReg);
	}
	output(strBucket);
}

void codeLeaLocal(int target, int var) {
	char tReg[REGSTR_LENGTH];
	char sVar[VARSTR_LENGTH];

	getRegStr(tReg, target);
	getVarStr(sVar, var);

	sprintf(strBucket, "%s\t%s, %s", LEA, tReg, sVar);
	output(strBucket);
}

void codeMoveReg(int target, int source) {
	char tReg[REGSTR_LENGTH];
	char sReg[REGSTR_LENGTH];

	if(target == source)
		return;

	getRegStr(tReg, target);
	getRegStr(sReg, source);

	sprintf(strBucket, "%s\t%s, %s", MOV, tReg, sReg);
	output(strBucket);
}

void codePushMem(int addr, int offset) {
	char regStr[REGSTR_LENGTH];
	getRegStr(regStr, offset);

	sprintf(strBucket, "%s\t%s [%s%d+%s]", PUSH, VARSIZE, GDATA_PRE, addr, regStr);
	output(strBucket);
}

void codePushReg(int reg, int mem){
	char regStr[REGSTR_LENGTH];
	getRegStr(regStr, reg);

	if(mem) {
		sprintf(strBucket, "%s\t%s [%s]", PUSH, VARSIZE, regStr);
	} else {
		sprintf(strBucket, "%s\t%s %s", PUSH, VARSIZE, regStr);
	}
	output(strBucket);
} 

void codePushInd(int idx) {
	char varStr[VARSTR_LENGTH];
	getVarStr(varStr, idx);
	sprintf(strBucket, "%s\t%s %s", PUSH, VARSIZE, varStr);
	output(strBucket);
}

void codePushCons(int constant) {
	sprintf(strBucket, "%s\t%s %d", PUSH, VARSIZE, constant);
	output(strBucket);
}

void codePushGlobalVar(int var, int offset) {
	if(offset >= 0) {
		sprintf(strBucket, "%s\t%s [%s%d+%d]", PUSH, VARSIZE, GDATA_PRE, var, offset);
	} else {
		sprintf(strBucket, "%s\t%s [%s%d%d]", PUSH, VARSIZE, GDATA_PRE, var, offset);
	}
	output(strBucket);
}

void codePushGlobalArray(int var) {
	sprintf(strBucket, "%s\t%s %s%d", PUSH, VARSIZE, GDATA_PRE, var);
	output(strBucket);
}

void codeCallFunc(int funcName) {
	sprintf(strBucket, "%s\t%s%d", CALLF, FUNC_PRE, funcName);
	output(strBucket);
}

void codeStartBss() {
	static int bssMark = 0;
	if(!bssMark) {
		strcpy(strBucket, "section .bss");
		output(strBucket);
		++bssMark;
	}
}

void codeStartText() {
	static int textMark = 0;

	if(!textMark) {
		strcpy(strBucket, "section .text");
		output(strBucket);
		++textMark;
	}
}

void codeDeclareGlobalVar(int varName, int size) {
	sprintf(strBucket, "%s%d:\t%s %d", GDATA_PRE, varName, GLOBAL_VAR_DEFINE, GLOBAL_VAR_LENGTH * size);
	output(strBucket);
}

void codeStartFunc(int funcName) {
	if(funcIsMain(funcName)) {
		strcpy(strBucket, "global _start\n_start:");
	} else {
		sprintf(strBucket, "global %s%d\n%s%d:", FUNC_PRE, funcName, FUNC_PRE, funcName);
	}
	output(strBucket);
	sprintf(strBucket, "%s\t%s", PUSH, EBP);
	output(strBucket);
	sprintf(strBucket, "%s\t%s, %s", MOV, EBP, ESP);
	output(strBucket);
}

void codeCleanStack(int height) {
	sprintf(strBucket, "%s\t%s, %d", ADD, ESP, height);
	output(strBucket);
}

void codeEndFunc(int funcName) {
	// sprintf(strBucket, "%s", LEAVE);
	output(LEAVE);

	if(!funcIsMain(funcName)) {
		output(RET);
	} else {
		codeEndMain();
	}
}

void codeSubEsp(int size) {
	sprintf(strBucket, "%s\t%s, %d", SUB, ESP, size);
	output(strBucket);
}

void codeTestCondition(int reg, int test, int labelNo) {
	char regStr[REGSTR_LENGTH];
	getRegStr(regStr, reg);

	sprintf(strBucket, "%s\t%s, %d", CMP, regStr, test);
	output(strBucket);
	sprintf(strBucket, "%s\t%s%d", JE, LABEL, labelNo);
	output(strBucket);
}

void codeOpAssign(int target, int source) {
	char tReg[VARSTR_LENGTH];
	char sReg[REGSTR_LENGTH];

	getRegStr(sReg, source);
	getRegStr(tReg, target);

	sprintf(strBucket, "%s\t%s [%s], %s", MOV, VARSIZE, tReg, sReg);
	output(strBucket);
}

int codeGetArrayOffset(int baseOff, int idxReg, int varLength, int global) {
	char regStr[REGSTR_LENGTH];
	getRegStr(regStr, idxReg);

	if(global == 0) {
		//  general local var
		sprintf(strBucket, "%s\t%s, %s", MOV, EBX, EBP);
		output(strBucket);
	} else if(global == -1) {
		// parameter, the array position in memory
		sprintf(strBucket, "%s\t%s, [%s+%d]", MOV, EBX, EBP, baseOff);
		output(strBucket);
	} else {
		// global var, just calculate the array index offset
		sprintf(strBucket, "%s\t%s, 0", MOV, EBX);
		output(strBucket);
	}

	// get the array index offset
	sprintf(strBucket, "%s\t%s, %d", IMUL, regStr, varLength);
	output(strBucket);

	sprintf(strBucket, "%s\t%s, %s", ADD, EBX, EAX);
	output(strBucket);

	if(global == 0) {
		sprintf(strBucket, "%s\t%s, %d", SUB, EBX, abs(baseOff));
		output(strBucket);
	}

	// store in ebx
	return 2;
}

// put the result in eax
int codeOpBinary(int v1, int v2, char *op) {
	char regStr1[REGSTR_LENGTH];
	char regStr2[REGSTR_LENGTH];

	getRegStr(regStr1, v1);
	getRegStr(regStr2, v2);

	int sar = 31;

	if (strcmp(op, "+") == 0) {
		sprintf(strBucket, "%s\t%s, [%s+%s]", LEA, EAX, regStr1, regStr2);
	} else if (strcmp(op, "-") == 0) {
		sprintf(strBucket, "%s\t%s, %s", SUB, regStr1, regStr2);
	} else if (strcmp(op, "*") == 0) {
		sprintf(strBucket, "%s\t%s, %s", IMUL, regStr1, regStr2);

	} else if (strcmp(op, "/") == 0) {
		sprintf(strBucket, "%s\t%s, %s", MOV, EDX, regStr1);
		output(strBucket);
		sprintf(strBucket, "%s\t%s, %d", SAR, EDX, sar);
		output(strBucket);
		sprintf(strBucket, "%s\t%s", IDIV, regStr2);

	} else {		/* relop */
		sprintf(strBucket, "%s\t%s, %s", CMP, regStr1, regStr2);
		output(strBucket);

		if (strcmp(op, "==") == 0) {
			sprintf(strBucket, "%s\t%s", SETE, AL);
		} else if (strcmp(op, "!=") == 0) {
			sprintf(strBucket, "%s\t%s", SETNE, AL);
		} else if (strcmp(op, ">") == 0) {
			sprintf(strBucket, "%s\t%s", SETG, AL);
		} else if (strcmp(op, "<") == 0) {
			sprintf(strBucket, "%s\t%s", SETL, AL);
		} else if (strcmp(op, ">=") == 0) {
			sprintf(strBucket, "%s\t%s", SETGE, AL);
		} else if (strcmp(op, "<=") == 0) {
			sprintf(strBucket, "%s\t%s", SETLE, AL);
		}

		output(strBucket);
		sprintf(strBucket, "%s\t%s, %s", MOVZX, EAX, AL);
	}

	output(strBucket);

	return 1;
}

int codeDataSection() {
	static int dataMark = 0;

	if(!dataMark) {
		strcpy(strBucket, "section .data");
		output(strBucket);
		strcpy(strBucket, "numbers db \"0123456789\", 0xA");
		output(strBucket);
		strcpy(strBucket, "inputchar db 0");
		output(strBucket);

		++dataMark;
		return 0;
	}

	return dataMark;
}

// output function
void codeFuncOutput() {
	// codeStartFunc();
	strcpy(strBucket, "sub esp, 4\nmov dword [ebp-4], 0\njmp G2\nG1:\nadd dword [ebp-4], 1\npush edx");
	output(strBucket);
	strcpy(strBucket, "G2:\nmov edx, 0\nmov eax, [ebp+8]\nmov ebx, 10\ndiv ebx\nmov [ebp+8], eax");
	output(strBucket);
	strcpy(strBucket, "cmp eax, 0\njnz G1\npush edx\nadd dword [ebp-4], 1\njmp G3");
	output(strBucket);
	strcpy(strBucket, "G4:\nsub dword [ebp-4], 1\npop edx\nmov eax, 4\nmov ebx, 1\nmov ecx, numbers");
	output(strBucket);
	strcpy(strBucket, "add ecx, edx\nmov edx, 1\nint 80h");
	output(strBucket);
	strcpy(strBucket, "G3:\ncmp dword [ebp-4], 0\njnz G4\nmov eax, 4\nmov ebx, 1\nlea ecx, [numbers+10]");
	output(strBucket);
	strcpy(strBucket, "mov edx, 1\nint 80h");
	output(strBucket);
}

// input funciton
void codeFuncInput() {
	strcpy(strBucket, "sub esp, 4\nmov dword [ebp-4], 0\nmov byte [inputchar], 0\njmp G6");
	output(strBucket);
	strcpy(strBucket, "G5:\nmov dword eax, [ebp-4]\nmov ebx, 10\nmul ebx\nxor ecx, ecx");
	output(strBucket);
	strcpy(strBucket, "mov byte cl, [inputchar]\nsub ecx, 48\nadd eax, ecx\nmov dword [ebp-4], eax");
	output(strBucket);
	strcpy(strBucket, "G6:\nmov eax, 03h\nmov ebx, 00h\nmov ecx, inputchar\nmov edx, 01h");
	output(strBucket);
	strcpy(strBucket, "int 80h\ncmp byte [inputchar], 0ah\njne G5\nmov dword eax, [ebp-4]");
	output(strBucket);
}


static void codeEndMain() {
	sprintf(strBucket, "mov ebx, eax\nmov eax,1\nint 80h");
	output(strBucket);
}