#ifndef _INDEX_CPP
#define _INDEX_CPP

#include "miniSQL.h"
#include "Index.h"
#include "test.h"
class BaseNode;
void BlockIni(BaseNode * BsNd);

//------------------------functions of BaseNode-------------------------
BaseNode::BaseNode(BaseNode &b){
	tableId = b.tableId;
	indexId = b.indexId;
	type = b.type;
	keyLen = b.keyLen;
	KeyOffset = b.KeyOffset;
	TupleLen = b.TupleLen;
	capacity = b.capacity;
}

char *BaseNode::Key(int offset){
	if(isLeaf)
		return &data[offset*TupleLen + KeyOffset];
	else
		return &data[offset*TupleLen];
}

char *BaseNode::Pointer(int offset){
	if(isLeaf)
		throw DbEr();
	return &data[offset*TupleLen + keyLen];
}

char *BaseNode::Record(int offset){
	return &data[offset*TupleLen];
}

void BaseNode::WriteKey(int offset, const char *key){
	int start = offset*TupleLen;

	if(isLeaf)
		start += KeyOffset;
	for(int i = 0; i < keyLen; i++){
		data[start + i] = key[i];
	}
}

void BaseNode::WritePointer(int offset, int id){
	int start = offset*TupleLen + keyLen;

	for(int i = 0; i < sizeof(id); i++){
		data[start + i] = *((char *)&id + i);
	}
}

void BaseNode::WriteRecord(int offset, const char *record){
	int start = offset*TupleLen;

	for(int i = 0; i < TupleLen; i++){
		data[start + i] = record[i];
	}
}

void BaseNode::CopyData(int source, int destination){
	int s = source*TupleLen;
	int d = destination*TupleLen;

	for(int i = 0; i < TupleLen; i++){
		data[d + i] = data[s + i];
	}
}

//------------------------functions of TypeChange-----------------------
int DataToPointer(char *data){
	return int(*(int *)data);
}

void BlockIni(BaseNode * BsNd)  //initialize the block for key length, tuple length, capacity and key offset
{
	TableInfo* TlIf;
	IndexInfo* IdIf;
	int keySize = 0;
	ListTableInfo::iterator itTbl;
	bool tag = false;
	for(itTbl = catalogInfo.tableInfoList.begin(); itTbl != catalogInfo.tableInfoList.end(); itTbl++)
	{
		ListIndexInfo::iterator itId;
		for(itId = (*itTbl)->indexInfoList.begin(); itId != (*itTbl)->indexInfoList.end(); itId++)
		{
			if((*itId)->indexID == BsNd->indexId)
			{
				KeyInfo* temp = (KeyInfo*)((*itId)->indexKey);
				keySize = temp->keySize;
				TlIf =(TableInfo*) (*itId)->indexTable;
				IdIf = *itId;
				tag = true;
				break;
			}
		}
		if(tag)break;
	}

	ListKeyInfo::iterator itr;
	KeyInfo *keyif = (KeyInfo*)IdIf->indexKey;
	int Keyoffset =0;
	int tupleLength =0;
	int cap = 0;
	for(itr = TlIf->keyInfoList.begin(); itr != TlIf->keyInfoList.end(); itr++)
		tupleLength+=(*itr)->keySize;
	for(itr = TlIf->keyInfoList.begin(); itr != TlIf->keyInfoList.end(); itr++)
	{
		if((*itr)->keyName == keyif->keyName)break;
		Keyoffset += (*itr)->keySize;
	}
	cap = (BLOCK_SIZE-50)/tupleLength;

	BsNd->keyLen = (*itr)->keySize;
	BsNd->KeyOffset = Keyoffset;
	BsNd->TupleLen = tupleLength;
	IndexInfo * I = TlIf->FindIndex(BsNd->indexId);
	KeyInfo *K = (KeyInfo*)I->indexKey;
	BsNd->type = K->keyType;
	if(!BsNd->isLeaf) 
	{
		BsNd->capacity = (BLOCK_SIZE-50)/(keySize + sizeof(int))-1;
		BsNd->KeyOffset = 0;
	}
	else
		BsNd->capacity = cap - 1;

}

//------------------------functions of FindIndex------------------------
//template <class Type>
Address FindIndex(int tableId, int indexId, TKey key){
	int i, j;
	int blockId = catalogInfo.GetRootBlockId(tableId, indexId);
	int offset;
	BaseNode * GetBlock(int blockId);

	if(blockId == -1)
		return Address(indexId, NOT_FOUND);
		//throw(ErIndexNotExist());

	blockId = FindLeafBlock(blockId, key);

	BaseNode *t = (BaseNode *)GetBlock(blockId);
	offset = FindKeyInLeaf(t, key);

	return Address(blockId, offset);
}

//template <class Type>
int FindLeafBlock(int blockId, TKey key){
	int k;
	BaseNode *t = (BaseNode *)GetBlock(blockId);

	while(!t->isLeaf){
		k = FindKeyInNonleaf(t, key);
		blockId = DataToPointer(t->Pointer(k));
		t = (BaseNode *)GetBlock(blockId);
	}

	return blockId;
}

//template <class Type>
int FindKeyInNonleaf(BaseNode *t, TKey key){
	int i;
	for(i = 1; i < t->num; i++){
		if(TKey(t->Key(i), t->type) > key)
			break;
	}
	return (i - 1);
}

//template <class Type>
int FindKeyInLeaf(BaseNode *t, TKey key){
	int i;
	for(i = 0; i < t->num; i++){
		if(TKey(t->Key(i), t->type) == key){
			return i;
		}
	}
	return -1;
}

//------------------------functions of InsertIndex------------------------
//template <class Type>
Address InsertIndex(int tableId, int indexId, TKey key){
	int i, j;
	int blockId;	///< the target block ID
	int offset;		///< the offset of the new key in the target block
	BaseNode *p;
	int pb = catalogInfo.GetRootBlockId(tableId, indexId);

	if(key == TKey(209059) || key == TKey(283490)){
		i = 0;
	}
	// if the index tree is empty
	if(pb == -1){
		pb = catalogInfo.NewBlock();
		p = (BaseNode *)GetNewBlock(pb);
		p->blockId = pb;
		p->tableId = tableId;
		p->indexId = indexId;
		p->isLeaf = true;
		p->isRoot = true;
		BlockIni(p);
		p->parent = -1;
		p->next = -1;
		p->num = 1;
		p->WriteKey(0, key.toData());		
#ifdef DEBUG
		p->capacity = FAN_OUT - 1;
#endif

		catalogInfo.UpdateRootBlockId(tableId, indexId, pb);
		catalogInfo.UpdateDataBlockId(tableId, indexId, pb);

		return Address(pb, 0);
	}

	// if this index tree isn't empty
	pb = FindLeafBlock(pb, key);
	p = (BaseNode *)GetBlock(pb);

	//cout << "FindLeaf: " << pb << endl;

	if(p->num < p->capacity){
		// the node space is enough
		blockId = pb;
		offset = InsertInLeaf(p, key);

		//cout << "Insert Offset: " << offset << endl;
	}
	else{
		// the node is full
		// create a new block to split
		int qb = catalogInfo.NewBlock();
		BaseNode *q = (BaseNode *)GetNewBlock(qb);
		*q = *p;
		q->blockId = qb;
		q->isLeaf = true;
		q->isRoot = false;
		q->parent = -1;
		q->num = 0;
		q->next = p->next;
		p->next = qb;
#ifdef DEBUG
		q->capacity = FAN_OUT - 1;
#endif

		// increase the p's capacity temporarily to insert the new key
		p->capacity++;
		offset = InsertInLeaf(p, key);

		//cout << "Insert Offset: " << offset << endl;

		// split p
		CopyBlock(p, (p->capacity+1)/2, p->capacity/2, q, 0);
		p->num = (p->capacity+1)/2;
		q->num = p->capacity/2;
		p->capacity--;
		if(offset < p->num){
			blockId = pb;
		}
		else{
			blockId = qb;
			offset -= p->num;
		}

		// adjust their parent
		key = TKey(q->Key(0), q->type);
		InsertInParent(p, key, q);
	}
	
	return Address(blockId, offset);
}

//template <class Type>
int InsertInNonleaf(BaseNode *p, TKey key){
	int i;
	// search in [1, num - 1]
	for(i = p->num - 1; i > 0; i--){
		if(TKey(p->Key(i), p->type) > key){
			p->CopyData(i, i + 1);
		}
		else
			break;
	}
	p->WriteKey(i + 1, key.toData());
	p->num++;

	return (i + 1);
}

//template <class Type>
int InsertInLeaf(BaseNode *p, TKey key){
	int i;
	// search in [0, num - 1]
	for(i = p->num - 1; i >= 0; i--){
		if(TKey(p->Key(i), p->type) > key){
			p->CopyData(i, i + 1);
		}
		else
			break;
	}
	p->WriteKey(i + 1, key.toData());
	p->num++;

	if(i == -1 && !p->isRoot){
		UpdateParentKey((BaseNode *)GetBlock(p->parent),
			TKey(p->Key(1), p->type), TKey(p->Key(0), p->type));
	}

	return (i + 1);
}

//template <class Type>
void InsertInParent(BaseNode *p, TKey key, BaseNode *q){
	int offset;
	int rb;
	BaseNode *r;

	// if p is the root, create a new root for p and q
	if(p->isRoot){
		rb = catalogInfo.NewBlock();
		r = (BaseNode *)GetNewBlock(rb);
		*r = *p;
		r->blockId = rb;
		r->isLeaf = false;
		r->isRoot = true;
		r->capacity = (BLOCK_SIZE-50)/(r->keyLen+sizeof(int)) - 1;
		r->parent = r->next = -1;
		r->num = 2;
		r->WritePointer(0, p->blockId);
		r->WritePointer(1, q->blockId);
		r->WriteKey(0, p->Key(0));
		r->WriteKey(1, key.toData());
#ifdef DEBUG
		r->capacity = FAN_OUT - 1;
#endif

		p->isRoot = q->isRoot = false;
		p->parent = q->parent = rb;

		catalogInfo.UpdateRootBlockId(r->tableId, r->indexId, rb);
		return;
	}

	// if p has a parent, try to insert in it
	rb = p->parent;
	r = (BaseNode *)GetBlock(rb);
	if(r == NULL)
		throw ErTest();
	if(r->num < r->capacity){
		// If the parent's capacity is enough, insert into it
		offset = InsertInNonleaf(r, key);
		r->WritePointer(offset, q->blockId);
		q->parent = rb;
	}
	else{
		// If the parent is full, split it
		// create a new block to split
		int sb = catalogInfo.NewBlock();
		BaseNode *s = (BaseNode *)GetNewBlock(sb);
		*s = *r;
		s->blockId = sb;
		s->num = 0;
		s->isLeaf = false;
		s->isRoot = false;
		s->parent = s->next = -1;
#ifdef DEBUG
		s->capacity = FAN_OUT - 1;
#endif

		// increase the r's capacity temporarily to insert the new key
		r->capacity++;
		offset = InsertInNonleaf(r, key);
		r->WritePointer(offset, q->blockId);

		// split r
		CopyBlock(r, (r->capacity+1)/2, r->capacity/2, s, 0);
		r->num = (r->capacity+1)/2;
		s->num = r->capacity/2;
		r->capacity--;

		// adjust children's parent
		BaseNode *t;
		if(offset < r->num)
			q->parent = p->parent;
		for(int i = 0; i < s->num; i++){
			BaseNode *t = (BaseNode *)GetNewBlock(DataToPointer(s->Pointer(i)));
			t->parent = sb;
		}

		// adjust their parent
		InsertInParent(r, TKey(s->Key(0), s->type), s);
	}
}

//template <class Type>
void CopyBlock(BaseNode *p, int ps, int len, BaseNode *q, int qs){
	for(int i  = 0; i < len; i++){
		q->WriteRecord(qs + i, p->Record(ps + i));
	}
}

//------------------------functions in DeleteIndex------------------------
//template <class Type>
Address DeleteIndex(int tableId, int indexId, TKey key){
	int pb = catalogInfo.GetRootBlockId(tableId, indexId);

	if(pb == -1)
		throw ErIndexNotExist();

	pb = FindLeafBlock(pb, key);
	BaseNode *p = (BaseNode *)GetBlock(pb);
	return DeleteEntry(p, key);
}

//template <class Type>
Address DeleteEntry(BaseNode *p, TKey key){
	int pb, qb, rb, sb;
	int offset;
	Address addr;
	BaseNode *q, *r, *s;

	// get the offset of p's key in its parent q
	pb = p->blockId;
	if(!p->isRoot){
		qb = p->parent;
		q = (BaseNode *)GetBlock(qb);
		offset = FindKeyInNonleaf(q, TKey(p->Key(0), p->type));
	}

	//cout << "---------Delete " << key << " from block " << pb << endl;
	//PrintIndex(pb, p);

	addr = DeleteKey(p, key);

	// remove the root if necessary
	if(p->isRoot && p->num <= 1){
		if(p->isLeaf){
			if(!p->num){
				catalogInfo.FreeBlock(pb);
				catalogInfo.UpdateRootBlockId(p->tableId, p->indexId, -1);
				catalogInfo.UpdateDataBlockId(p->tableId, p->indexId, -1);
				addr.offset = NOTFOUND;
			}
			return addr;
		}
		qb = DataToPointer(p->Pointer(0));
		q = (BaseNode *)GetBlock(qb);
		q->isRoot = true;
		q->parent = -1;
		catalogInfo.FreeBlock(pb);
		catalogInfo.UpdateRootBlockId(q->tableId, q->indexId, qb);

		return addr;
	}

	// nothing to adjust
	if(p->num >= (p->capacity + 1) / 2 || p->isRoot){
		// get the address of the next record
		if(p->isLeaf && addr.offset == p->num){
			if(p->next == NOTFOUND)
				addr.offset = NOTFOUND;
			else{
				addr.blockId = p->next;
				addr.offset = 0;
			}
		}
		return addr;
	}

	// borrow an entry from left sibling
	if(offset > 0){
		rb = DataToPointer(q->Pointer(offset - 1));
		r = (BaseNode *)GetBlock(rb);
		if(r->num > (r->capacity+1)/2){
			// add the key to the block
			p->num++;
			RightShift(p, p->num - 1, 1);
			p->WriteRecord(0, r->Record(r->num - 1));
			// delete the key from the left sibling
			r->num--;
			// update their parent's key
			UpdateParentKey(q, TKey(p->Key(1), p->type), TKey(p->Key(0), p->type));

			// get the address of the next record
			addr.offset++;
			if(p->isLeaf && addr.offset == p->num){
				if(p->next == NOTFOUND)
					addr.offset = NOTFOUND;
				else{
					addr.blockId = p->next;
					addr.offset = 0;
				}
			}
			return addr;
		}
	}

	// borrow an entry from right sibling
	if(offset < q->num - 1){
		rb = DataToPointer(q->Pointer(offset + 1));
		r = (BaseNode *)GetBlock(rb);
		if(r->num > (r->capacity+1)/2){
			// add the key to the block
			p->num++;
			p->WriteRecord(p->num - 1, r->Record(0));
			// delete the key from the right sibling
			r->num--;
			LeftShift(r, 0, 1);
			// update their parent's key
			UpdateParentKey(q, TKey(p->Key(p->num - 1), p->type), TKey(r->Key(0), r->type));

			return addr;
		}
	}

	// coalesce the block to the left sibling
	if(offset > 0){
		rb = DataToPointer(q->Pointer(offset - 1));
		r = (BaseNode *)GetBlock(rb);
		// adjust the next or the children's parent
		if(p->isLeaf)
			r->next = p->next;
		else{
			for(int i = 0; i < p->num; i++){
				sb = DataToPointer(p->Pointer(i));
				s = (BaseNode *)GetBlock(sb);
				s->parent = rb;
			}
		}
		// copy the block data to its left sibling
		CopyBlock(p, 0, p->num, r, r->num);
		addr.blockId = rb;
		addr.offset += r->num;
		r->num += p->num;
		// Free the block
		catalogInfo.FreeBlock(pb);

		// delete the entry in the parent node
		DeleteEntry(q, TKey(p->Key(0), p->type));

		// get the address of the next record
		if(r->isLeaf && addr.offset == r->num){
			if(r->next == NOTFOUND)
				addr.offset = NOTFOUND;
			else{
				addr.blockId = r->next;
				addr.offset = 0;
			}
		}
		return addr;
	}

	// coalesce the block to the right sibling
	if(offset < q->num - 1){
		// adjust the next or the children's parent
		if(p->isLeaf)
			p->next = r->next;
		else{
			for(int i = 0; i < r->num; i++){
				sb = DataToPointer(r->Pointer(i));
				s = (BaseNode *)GetBlock(sb);
				s->parent = pb;
			}
		}
		// copy the right sibling data to itself
		CopyBlock(r, 0, r->num, p, p->num);
		p->num += r->num;
		// Free the block
		catalogInfo.FreeBlock(rb);

		// delete the entry in the parent node
		DeleteEntry(q, TKey(r->Key(0), r->type));

		return addr;
	}

	// the number of entries is too small, and unhandled
	throw ErUnknownError();
}

//template <class Type>
Address DeleteKey(BaseNode *p, TKey key){
	int offset;

	if(p->isLeaf)
		offset = FindKeyInLeaf(p, key);
	else
		offset = FindKeyInNonleaf(p, key);
	if(offset == -1 || TKey(p->Key(offset), p->type) != key)
		throw ErKeyNotFound();

	// update their parent's key
	if(!offset && !p->isRoot){
		UpdateParentKey((BaseNode *)GetBlock(p->parent),
			TKey(p->Key(0), p->type), TKey(p->Key(1), p->type));
	}
	// delete the key
	p->num--;
	LeftShift(p, offset, 1);

	return Address(p->blockId, offset);
}

//template <class Type>
void UpdateParentKey(BaseNode *p, TKey oldKey, TKey newKey){
	int offset;

	offset = FindKeyInNonleaf(p, oldKey);
	p->WriteKey(offset, newKey.toData());
	if(offset == 0 && !p->isRoot){
		UpdateParentKey((BaseNode *)GetNewBlock(p->parent), oldKey, newKey);
	}
}

//template <class Type>
void LeftShift(BaseNode *p, int start, int len){
	int end;

	if(p->num > p->capacity -len)
		end = p->capacity - len;
	else
		end = p->num;
	for(int i = start; i < end; i++){
		p->WriteRecord(i, p->Record(i + len));
	}
}

//template <class Type>
void RightShift(BaseNode *p, int start, int len){
	for(int i = start; i >= len; i--){
		p->WriteRecord(i, p->Record(i - len));
	}
}

//------------------------functions in DropIndex------------------------
//template <class Type>
void DropIndex(int tableId, int indexId){
	int i;
	int pb;
	BaseNode *p;
	queue<int> que;

	pb = catalogInfo.GetRootBlockId(tableId, indexId);
	if(pb == -1){
		return;
		//throw ErIndexNotExist();
	}

	que.push(pb);
	while(!que.empty()){
		pb = que.front();
		que.pop();
		p = (BaseNode *)GetBlock(pb);
		if(!p->isLeaf)
			for(i = 0; i < p->num; i++)
				que.push(DataToPointer(p->Pointer(i)));
		catalogInfo.FreeBlock(pb);
	}

	catalogInfo.UpdateRootBlockId(tableId, indexId, -1);
	catalogInfo.UpdateDataBlockId(tableId, indexId, -1);
}


#endif