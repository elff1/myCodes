#ifndef _Buffer_H
#define _Buffer_H

#include<stdio.h>
#include<stdlib.h>

#include "miniSQL.h"
#include "Index.h"


void Testprint();

class BaseNode;

/*Define node of a blockInfo list*/
struct ListNode{
	int blockNum;
	int arrayNum;
	bool lock;
	struct ListNode *next;
};



/* Initialize buffer.*/
void InitBuffer();


/* Open database file.*/
void OpenFile();


/* Initialize the list with size same as block array.*/
void InitializeList();


/* Initialize the block array in buffer.*/
void InitBlockArray();


/* Move the node matching the block used to the list head.*/
void MoveToHead(struct ListNode *last,struct ListNode *recent);



/* Given a blockID,search for the block in buffer. */
BaseNode *GetBlock(int blockID);

/* Given a blockID, add the new block into buffer*/
void *GetNewBlock(int blockID);


/* Write data in block back to file. */
void WriteBack(BaseNode *block);


/* Read data from disk into buffer.*/
void ReadFromDisk(int blockID,BaseNode *blockInBuffer);


/* Judge if the block is dirty.*/
bool IsDirty(BaseNode *block);

/* judge if the block is locked*/
bool IsLocked(BaseNode *block);

/* Quit the database system.*/
void BufferDispose();

#endif // _Buffer_H