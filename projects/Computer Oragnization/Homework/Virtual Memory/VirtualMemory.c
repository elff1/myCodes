#include <stdio.h>
#include <string.h>

#define VirtualSize 2048
#define PhysicalSize 512
#define PageSize 128
#define BufSize 512

#define VirNum (VirtualSize / PageSize)
#define PhyNum (PhysicalSize / PageSize)

typedef unsigned char byte;
typedef struct vp{
	char v;
	int addr;
}PageTable;
typedef struct pp{
	byte data[PageSize];
	int count;
}PhysicalPage;

void initialize();
int LRU();
byte GetMemory(int addr);

PageTable pageTable[VirNum];
PhysicalPage phyPage[PhyNum];

int main(){
	char c;
	short i, j, temp;
	int addr;
	char buf[BufSize];
	FILE * fp;

	initialize();
	printf("Enter the address you want to access in decimal. Enter \"q\" to exit.\n");
	gets_s(buf, BufSize);
	while(strcmp(buf, "q")){
		sscanf(buf, "%d", &addr);
		printf("The data in the address is: %02X\n\n", GetMemory(addr));
		gets_s(buf, BufSize);
	}
}

void initialize(){
	byte data[VirtualSize];
	int i, j;
	int temp;
	FILE *fp;

	for(i = 0; i < PhyNum; i++){
		phyPage[i].count = 0;
	}
	for(i = 0; i < VirNum; i++){
		pageTable[i].v = 0;
	}

	for(i = 0; i < VirNum; i++){
		temp = 0;
		for(j = 0; j < PageSize; j++){
			data[i * PageSize + j] = temp % 256;
			temp += (i + 1);
		}
	}
	
	fp = fopen("Virtual", "wb");
	fwrite(data, 1, VirtualSize, fp);
	fclose(fp);
}

int LRU(){
	int i, p;
	int leastCount = phyPage[0].count;
	int leastNo = 0;

	for(i = 0; i < PhyNum; i++)
		if(!phyPage[i].count)
			return i;
		else if(phyPage[i].count < leastCount){
			leastCount = phyPage[i].count;
			leastNo = i;
		}

	for(i = 0; i < VirNum; i++)
		if(pageTable[i].v && pageTable[i].addr == leastNo){
			pageTable[i].v = 0;
			phyPage[leastNo].count = 0;
		}

	return leastNo;
}

byte GetMemory(int addr){
	int p, p1, i;
	int pag, ofs;
	FILE *fp;

    pag = addr / PageSize;
    ofs = addr % PageSize;        
    	
	if(pageTable[pag].v){
		phyPage[pageTable[pag].addr].count++;
		printf("The page is in the physical memory %d.\n", pageTable[pag].addr);
		printf("The current page is %X.\n", pag);
		printf("The current offset is %X.\n", ofs);
		return phyPage[pageTable[pag].addr].data[ofs];
	}
       
    p = LRU();
	pageTable[pag].v = 1;
	pageTable[pag].addr = p;
	phyPage[p].count = 1;

	fp = fopen("Virtual", "rb");
	fseek(fp, pag * PageSize, 0);
	fread(phyPage[p].data, 1, PageSize, fp);
	fclose(fp);
	printf("The page isn't in the physical memory, and now write into memory %d.\n", p);
	printf("The current page is %X.\n", pag);
	printf("The current offset is %X.\n", ofs);
    
	return phyPage[p].data[ofs];
}