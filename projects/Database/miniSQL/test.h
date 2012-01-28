#ifndef _TEST_H
#define _TEST_H

#include "Index.h"

// 传入当前块号，输出该块及以下各块数据
void PrintIndex(int blockId);

// 传入非叶子块指针，输出该块数据
void PrintNonleaf(BaseNode *p);

// 传入叶子块指针，输出该块数据
void PrintLeaf(BaseNode *p);

// 传入当前块指针，从该块开始，顺序输出数据
void PrintData(BaseNode *p);

// 传入当前块指针及tuple首地址，输出tuple中各属性值
void PrintTuple(BaseNode *p, char *tuple);

#endif // _TEST_H