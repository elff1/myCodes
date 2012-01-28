#include "miniSQL.h"
#include "test.h"

extern CatalogInfo catalogInfo;

void PrintIndex(int blockId){
	int i;
	int pb;
	BaseNode *p;
	queue<int> que;

	//pb = catalogInfo.GetRootBlockId(indexId);
	pb = blockId;
	if(pb == -1){
		cout << "Empty index" << '\n' << endl;
		return;
	}

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
	cout << '\n' << endl;
}

void PrintData(BaseNode *p){
	int i;
	int pb;
//	BaseNode *p;

	cout << "The whole data:" << endl;
	if(!p)
		return;
	pb = p->blockId;
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
