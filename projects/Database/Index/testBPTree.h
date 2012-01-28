#ifndef _testBPTree_H
#define _testBPTree_H

#include <queue>
#include "TKey.h"
#include "miniSQL.h"
#include "BPTree.h"

// Buffer
extern BaseNode blocks[BlockNum];

// Catalog
extern bool blockUsed[BlockNum];
extern int indexRootBlockId[IndexNum];
extern int indexDataBlockId[IndexNum];
extern DataType indexType[IndexNum];

// Buffer
void *GetNewBlock(int blockId);
/** return NULL if block not exist */
void *GetBlock(int blockId);

// Catalog
int NewBlock(void);
void FreeBlock(int blockId);
bool IsBlockUsed(int blockId);
int GetRootBlockId(int indexId);
int GetDataBlockId(int indexId);
void UpdateRootBlockId(int indexId, int blockId);
void UpdateDataBlockId(int indexId, int blockId);
void PrintCatalog();

DataType GetIndexType(int indexId);

// test Index
void PrintIndex(int indexId, BaseNode *p);
void PrintNonleaf(BaseNode *p);
void PrintLeaf(BaseNode *p);
void PrintData(int pb, BaseNode *p);

#endif // _testBPTree_H