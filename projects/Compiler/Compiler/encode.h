#ifndef __ENCODE_H
#define __ENCODE_H

#define LABEL "L"
#define CMP "cmp"
#define JNE "jne"
#define JE "je"
#define MOV "mov"
#define JMP "jmp"
#define PUSH "push"
#define POP "pop"
#define ADD "add"
#define SUB "sub"
#define IMUL "imul"
#define IDIV "idiv"
#define LEA "lea"
#define LEAVE "leave"
#define RET "ret"
#define SAR "sar"
#define CMP "cmp"
#define SETE "sete"
#define SETNE "setne"
#define SETG "setg"
#define SETL "setl"
#define SETGE "setge"
#define SETLE "setle"
#define MOVZX "movzx"
#define CALLF "call"

#define EAX "eax"
#define EBX "ebx"
#define ECX "ecx"
#define EDX "edx"
#define EBP "ebp"
#define ESP "esp"
#define AL "al"

#define VARSIZE "dword"
#define GLOBAL_VAR_LENGTH 2
#define GLOBAL_VAR_DEFINE "resw"
#define VARSTR_LENGTH 20	/* for [ebp-4] ... */
#define REGSTR_LENGTH 4

#define MAX_STR_LENGTH 300

#define FUNC_PRE "F_"
#define GDATA_PRE "D_"

char strBucket[MAX_STR_LENGTH];

unsigned int ELFHash(const char *str, unsigned int len);
void output(const char *str);
static int funcIsMain(int funcName);
static void getVarStr(char *varStr, int offset);
static int getRegStr(char *regStr, int reg);
int creatLabel();
void codeLabel(int labelNo);
void codeJmp(int labelNo);
void codePop(int reg);
void codeLeaGlobal(int target, int addr, int offset);
void codeLeaLocal(int target, int var);
void codeMoveReg(int target, int source);
void codePushMem(int addr, int offset);
void codePushReg(int reg, int mem);
void codePushInd(int idx);
void codePushCons(int constant);
void codePushGlobalVar(int var, int offset);
void codePushGlobalArray(int var);
void codeCallFunc(int funcName);
void codeStartBss();
void codeStartText();
void codeDeclareGlobalVar(int varName, int size);
void codeStartFunc(int funcName);
void codeCleanStack(int height);
void codeEndFunc(int funcName);
void codeSubEsp(int size);
void codeTestCondition(int reg, int test, int labelNo);
void codeOpAssign(int target, int source);
int codeGetArrayOffset(int baseOff, int idxReg, int varLength, int global);
int codeOpBinary(int v1, int v2, char *op);

int codeDataSection();
void codeFuncOutput();
void codeFuncInput();
static void codeEndMain();

extern FILE *fout;

#endif
