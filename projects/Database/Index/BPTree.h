/*
* Fixed Bugs:
*	1. if the first key of block changed, its parent's didn't updated
*	2. 若表为空，去掉抛异常
* TODO: 1. watch out "ErUnknown"
*		2. 
*/

#ifndef _BPTree_H
#define _BPTree_H

#include "miniSQL.h"
#include "TKey.h"
//#include "testBPTree.h"

class Address{
public:
	int blockId;	///< the block ID
	int offset;		///< the offset in the block
	Address(){}
	Address(int b, int o){
		blockId = b;
		offset = o;
	}
};

class BaseNode{
public:
	int blockId;
	int tableId;
	int indexId;
	bool isRoot;
	bool isLeaf;
	DataType type;
	int keyLen;
	int parent;
	int next;
	int capacity;	///< the capcity of children, 4000/size - 1
	int num;		///< the number of children
	int KeyOffset; ///< the offset of key in every tuple
	int TupleLen;  //< the length of every tuple

	bool dirty;
	bool lock;
	int time;

	char data[DATA_LEN];

	BaseNode(){}
	BaseNode(BaseNode &);
	~BaseNode(){}

	///* @
	(char *)Key(int offset);
	(char *)Pointer(int offset);
	(char *)Record(int offset);
	void WriteKey(int offset, const char *key);
	void WritePointer(int offset, int id);
	void WriteRecord(int offset, const char *record);
	void CopyData(int source, int destination);
};

int DataToPointer(char *data);

void BlockIni(BaseNode * BsNd);

//------------------------API functions of Index------------------------
void DropIndex(int tableId, int indexId);

Address FindIndex(int tableId, int indexId, TKey key);

Address InsertIndex(int tableId, int indexId, TKey key);

Address DeleteIndex(int tableId, int indexId, TKey key);

//------------------------functions in FindIndex------------------------
/**
* @brief find the leaf block in the index, which contains the key
* @param blockId the start block ID of the index
* @param key the target key
* @return int the target leaf block ID
*/
//template <class Type>
int FindLeafBlock(int blockId, TKey key);

/**
* @brief find the key in the target block
* @param p the target block pointer
* @param key the target key
* @return int the offset of the child pointer
*
* using sequential search or binary search
*/
//template <class Type>
int FindKeyInNonleaf(BaseNode *t, TKey key);

/**
* @brief find the key in the target block
* @param p the target block pointer
* @param key the target key
* @return int the offset of the target key
*			if not found, return -1
*
* using sequential search or binary search
*/
//template <class Type>
int FindKeyInLeaf(BaseNode *t, TKey key);

//------------------------functions in InsertIndex------------------------
/**
* @brief insert the key into the nonleaf block
* @param p the target block pointer
* @param key the new key to be inserted
* @return int the offset of the new key in the block
*/
//template <class Type>
int InsertInNonleaf(BaseNode *p, TKey key);

/**
* @brief insert the key into the leaf block
* @param p the target block pointer
* @param key the new key to be inserted
* @return int the offset of the new key in the block
*/
//template <class Type>
int InsertInLeaf(BaseNode *p, TKey key);

/**
* @brief insert the key into the parent's block
* @param p one child block pointer
* @param key the new key to be inserted
* @param q another child block pointer
* @return void
*/
//template <class Type>
void InsertInParent(BaseNode *p, TKey key, BaseNode *q);

/**
* @brief copy the data from one block to another
* @param p the source block pointer
* @param ps the start place of souce blcok
* @param len the copy length
* @param q the destination block pointer
* @param qs the start place of destination block
* @return void
*/
//template <class Type>
void CopyBlock(BaseNode *p, int ps, int len, BaseNode *q, int qs);

//------------------------functions in DeleteIndex------------------------
/**
* @brief delete an entry from the node
* @param p the block pointer
* @param key the key to be deleted
* @return void
*/
//template <class Type>
Address DeleteEntry(BaseNode *p, TKey key);

/**
* @brief delete an key from the node
* @param p the block pointer
* @param key the key to be deleted
* @return void
*/
//template <class Type>
Address DeleteKey(BaseNode *p, TKey key);

/**
* @brief update the key in the parent node
* @param p the block pointer
* @param oldKey the old key to be replaced
* @param newKey the new key
* @return void
*/
//template <class Type>
void UpdateParentKey(BaseNode *p, TKey oldKey, TKey newKey);

/**
* @brief left shift the block data
* @param p the block
* @param start the start offset of the block data
* @parem len the shift length
* @return void
*/
//template <class Type>
void LeftShift(BaseNode *p, int start, int len);

/**
* @brief right shift the block data
* @param p the block
* @param start the start offset of the block data
* @parem len the shift length
* @return void
*/
//template <class Type>
void RightShift(BaseNode *p, int start, int len);

#endif // _BPTree_H