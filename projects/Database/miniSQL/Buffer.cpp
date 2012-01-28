#ifndef _Buffer_CPP
#define _Buffer_CPP

#include "miniSQL.h"
#include "Buffer.h"



//------------------------------ Variable&Structure Definition-------------------------------------//

BaseNode BlockArray[buffer_size];				//Define the buffer with block array.
struct ListNode *head=(struct ListNode *)malloc(sizeof(struct ListNode));		//Define a head for list.
FILE *fp=NULL;



//---------------------------------- Test Function. -----------------------------------------//

void Testprint(){
	int i;
	struct ListNode *search=head->next;
	while(search!=NULL){
		printf("%d %d %d\n",search->arrayNum, search->blockNum, search->lock);
		search=search->next;
	}

	for(i=0;i<buffer_size;i++){
		printf("%d %d\n",BlockArray[i].blockId, BlockArray[i].lock);
		//printf("%s\n",BlockArray[i].data);
	}
}




//----------------------------- Initialization Function.---------------------------------------//

/******* Open the DB file.********/

void OpenFile(){
	if((fp=fopen(filename,"rb+"))==NULL){
		throw ErOpenFile();
	}
}



/********** Initialize the block array in buffer.***********/
void InitBlockArray(){
	int i;
	for(i=0;i<buffer_size;i++){
		BlockArray[i].blockId=-1;
		BlockArray[i].lock=false;
	}
}

/******** Initialize the list with size same as block array.********/

void InitializeList(){
	int i;
	struct ListNode *last=head;
	head->arrayNum=-1;
	head->blockNum=-1;
	head->next=NULL;
	for(i=0;i<buffer_size;i++){
		last->next=(struct ListNode *)malloc(sizeof(struct ListNode));
		last=last->next;
		last->arrayNum=-1;
		last->blockNum=-1;
		last->lock=false;
		last->next=NULL;
	}
}



/******** Initialize a buffer.*********/

void InitBuffer(){
	OpenFile();
	InitializeList();
	InitBlockArray();
}



//---------------------------- List Function.--------------------------------------//

/****** Move the node matching the block used to the list head.*******/

void MoveToHead(struct ListNode *last,struct ListNode *recent){
	if(last!=head){
		last->next=recent->next;
		recent->next=head->next;
		head->next=recent;
	}
}



//---------------------------- API Function.-----------------------------------------//

/********* Find the block RM/IM asks for.***********/

BaseNode *GetBlock(int blockID){
	if(blockID == -1)
		return NULL;
	struct ListNode *search=head->next;
	struct ListNode *last=head;
	struct ListNode *temp=last;
	int i;

	while(search!=NULL&&search->blockNum>=0){
		if(search->blockNum==blockID){				//Move the node to the head of the list.
			
			MoveToHead(last,search);

			return BlockArray+search->arrayNum;		//If such block is found,return the address in buffer.
		}
		else{
			if(search->lock==true){					//Move all locked block node to the head.
				MoveToHead(last,search);
				if(last==head)
					last=last->next;
				search=last->next;
			}
			else{
				temp=last;
				last=search;
				search=search->next;
			}
		}
	}

	if(search!=NULL){						//There exists empty blocks.
		for(i=0;i<buffer_size;i++){
			if(BlockArray[i].blockId<0){				//Find the empty block,read from disk and update List.
				ReadFromDisk(blockID,BlockArray+i);
				
				search->arrayNum=i;
				search->blockNum=blockID;
				search->lock = IsLocked(BlockArray + search -> arrayNum);

				MoveToHead(last,search);
				
				return BlockArray+i;
			}
		}
	}


//As all locked block nodes are moved to list head,the rear should be unlocked.
//If the rear is locked,all blocks are locked.Exception!

	if(IsLocked(BlockArray+last->arrayNum)){			
		throw ErLock();
	}

	if(IsDirty(BlockArray+last->arrayNum))				//Buffer is full,then use LRU algorithm: replace the rear of list.
		WriteBack(BlockArray+last->arrayNum);
	
	ReadFromDisk(blockID,BlockArray+last->arrayNum);
	
	last->blockNum=blockID;								//Update the list node information.
	last->lock=IsLocked(BlockArray+last->arrayNum);
	MoveToHead(temp,last);
	
	return BlockArray+last->arrayNum;
}



/****** Given a blockID, create a new block.******/

void *GetNewBlock(int blockID){
	struct ListNode *search=head->next;
	struct ListNode *last=head;
	struct ListNode *temp=last;
	int i;

	while(search!=NULL&&search->blockNum>=0){
		search->lock=BlockArray[search->arrayNum].lock;
		if(search->blockNum==blockID){				//Move the node to the head of the list.

			MoveToHead(last,search);

			return BlockArray+search->arrayNum;		//If such block is found,return the address in buffer.
		}
		else{
			if(search->lock==true){					//Move all locked block node to the head.
				MoveToHead(last,search);
				if(last==head)
					last=last->next;
				search=last->next;
			}
			else{
				temp=last;
				last=search;
				search=search->next;
			}
		}
	}
	
	
	if(search!=NULL){						//There exists empty blocks.
		for(i=0;i<buffer_size;i++){
			if(BlockArray[i].blockId<0){				//Find the empty block,update List and return to IndexManager.
				
				search->arrayNum=i;
				search->blockNum=blockID;
//				search->lock=IsLocked(BlockArray+search->blockNum);

				MoveToHead(last,search);
				
				return BlockArray+i;
			}
		}
	}


//As all locked block nodes are moved to list head,the rear should be unlocked.
//If the rear is locked,all blocks are locked.Exception!

	if(IsLocked(BlockArray+last->arrayNum)){			
		throw ErLock();
	}

	if(IsDirty(BlockArray+last->arrayNum))				//Buffer is full,then write back the list rear.
		WriteBack(BlockArray+last->arrayNum);

	last->blockNum=blockID;								//Update the list node.
	MoveToHead(temp,last);

	return BlockArray+last->arrayNum;

}




//--------------------------- File Funtion.---------------------------------------//

/******* Write data in buffer block back to disk.*******/

void WriteBack(BaseNode *block){
	FILE *fBlock=fp;
	rewind(fBlock);
	long offset;
	
	block->dirty=false;
	offset=block->blockId*BLOCK_SIZE;
	fseek(fBlock,offset,0);

	fwrite(block,BLOCK_SIZE,1,fBlock);
}



/******* Read data in disk into a block int buffer.********/

void ReadFromDisk(int blockID,BaseNode *blockInBuffer){
	FILE *fBlock=fp;
	rewind(fBlock);
	long offset;

	offset=blockID*BLOCK_SIZE;
	fseek(fBlock,offset,0);

	fread(blockInBuffer,BLOCK_SIZE,1,fBlock);
}



/******* Quit the database system.********/

void BufferDispose(){
	int i;
	struct ListNode *node=head;
	
	for(i=0;i<buffer_size;i++){					// Write back all blocks in buffer.
		BlockArray[i].lock=false;
		if(IsDirty(BlockArray+i))
			WriteBack(BlockArray+i);
	}

	while(node!=NULL){				// Free the block list.
		head=node->next;
		free(node);
		node=head;
	}

	fclose(fp);
}



//--------------------------- Internal Judgement.---------------------------------------//

/******** Judge if the block is dirty.*********/

bool IsDirty(BaseNode *block){
	return block->dirty;
};


/******** Judge if the block is locked.*********/

bool IsLocked(BaseNode *block){
	return block->lock;
};


//void main(){
//	
//}

#endif // _Buffer_CPP