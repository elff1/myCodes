#include "testBPTree.h"

// Buffer
void *GetNewBlock(int blockId){
	if(!IsBlockUsed(blockId))
		throw(ErBlockNotExist());
	return &blocks[blockId];
}

void *GetBlock(int blockId){
	if(!IsBlockUsed(blockId))
		throw(ErBlockNotExist());
	return &blocks[blockId];
}

// Catalog
int NewBlock(void){
	for(int i = 0; i < BlockNum; i++)
		if(!blockUsed[i]){
			blockUsed[i] = true;
			return i;
		}
	return -1;
}

void FreeBlock(int blockId){
	blockUsed[blockId] = false;
}

bool IsBlockUsed(int blockId){
	if(blockId < 0 || blockId >= BlockNum)
		return false;
	return blockUsed[blockId];
}

int GetRootBlockId(int indexId){
	return indexRootBlockId[indexId];
}

int GetDataBlockId(int indexId){
	return indexDataBlockId[indexId];
}

void UpdateRootBlockId(int indexId, int blockId){
	indexRootBlockId[indexId] = blockId;
}

void UpdateDataBlockId(int indexId, int blockId){
	indexDataBlockId[indexId] = blockId;
}

DataType GetIndexType(int indexId){
	return indexType[indexId];
}

void PrintCatalog(){
	int i;
	int count = 0;

	cout << "Used Blocks: ";
	for(i = 0; i < BlockNum; i++){
		if(blockUsed[i])
			count++;
			//cout << i << '\t';
	}
	cout << count << endl;

	cout << "Index information: \n";
	for(i = 0; i < IndexNum; i++)
		if(indexRootBlockId[i] >= 0)
			cout << "Index " << i 
				<< ": Root: " << indexRootBlockId[i]
				<< "; Data: " << indexDataBlockId[i] << '\n';
	cout << endl;
}

// test Index
void PrintIndex(int blockId, BaseNode *p){
	int i;
	int pb;
//	BaseNode *p;
	queue<int> que;

	//pb = GetRootBlockId(indexId);
	pb = blockId;
	p = (BaseNode *)GetBlock(pb);
	if(pb == -1){
		cout << "Empty index" << '\n' << endl;
		return;
	}

	cout << "Key length: " << p->keyLen
		<< "\tKey type: " << p->type
		<< "\tKey offset: " << p->KeyOffset
		<< "\tTuple length: " << p->TupleLen
		<< endl;

	que.push(pb);
	while(!que.empty()){
		pb = que.front();
		que.pop();
		p = (BaseNode *)GetBlock(pb);
		if(p->isLeaf)
			PrintLeaf(p);
		else{
			PrintNonleaf(p);
			for(i = 0; i < p->num; i++)
				que.push(DataToPointer(p->Pointer(i)));
		}
	}
}

void PrintNonleaf(BaseNode *p){
	int i;

	cout << "Block " << p->blockId << ": ";
	if(p->isRoot) cout << "Root" << ' ';
	cout << "Nonleaf" << ' ';
	cout << p->num << endl;
	cout << "Parent Block: " << p->parent << endl;
	//cout << '\t';
	for(i = 0; i < p->num; i++)
		cout << TKey(p->Key(i), p->type) << '\t';
	cout << endl;
	for(i = 0; i < p->num; i++)
		cout << DataToPointer(p->Pointer(i)) << '\t';
	cout << '\n' << endl;
}

void PrintLeaf(BaseNode *p){
	int i;

	cout << "Block " << p->blockId << ": ";
	if(p->isRoot) cout << "Root" << ' ';
	cout << "Leaf" << ' ';
	cout << p->num << endl;
	cout << "Parent Block: " << p->parent << endl;
	for(i = 0; i < p->num; i++)
		cout << TKey(p->Key(i), p->type) << '\t';
	cout << endl;
	/*for(i = 0; i < p->num; i++)
		cout << DataToPointer(p->Pointer(i)) << '\t';*/
	//cout << '\n' << endl;
}

void PrintData(int pb, BaseNode *p){
	int i;
//	BaseNode *p;

	cout << "The whole data:" << endl;
	while(pb != NOT_FOUND){
		p = (BaseNode *)GetBlock(pb);
		cout << "Leaf Block " << pb << ":\t";
		for(i = 0; i < p->num; i++)
			cout << TKey(p->Key(i), p->type) << '\t';
		cout << endl;

		pb = p->next;
	}
	cout << endl;
}
