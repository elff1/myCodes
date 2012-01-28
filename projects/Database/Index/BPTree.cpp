#include <memory.h>
#include "testBPTree.h"
#include "BPTree.h"

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
		throw ErPrintPointer();
	return &data[offset*TupleLen + KeyOffset + keyLen];
}

char *BaseNode::Record(int offset){
	return &data[offset*TupleLen];
}

void BaseNode::WriteKey(int offset, const char *key){
	int start = offset*TupleLen;

	if(isLeaf)
		start += KeyOffset;
	/*for(int i = 0; i < keyLen; i++){
		data[start + i] = key[i];
	}*/
	memcpy(data + start, (void *)key, keyLen);
}

void BaseNode::WritePointer(int offset, int id){
	int start = offset*TupleLen + KeyOffset + keyLen;

	/*for(int i = 0; i < sizeof(id); i++){
		data[start + i] = *((char *)&id + i);
	}*/
	memcpy(data + start, &id, sizeof(id));
}

void BaseNode::WriteRecord(int offset, const char *record){
	int start = offset*TupleLen;

	/*for(int i = 0; i < TupleLen; i++){
		data[start + i] = record[i];
	}*/
	memcpy(data + start, record, TupleLen);
}

void BaseNode::CopyData(int source, int destination){
	int s = source*TupleLen;
	int d = destination*TupleLen;

	/*for(int i = 0; i < TupleLen; i++){
		data[d + i] = data[s + i];
	}*/
	memcpy(data + d, data + s, TupleLen);
}

//------------------------functions of TypeChange-----------------------
int DataToPointer(char *data){
	return int(*(int *)data);
}

void BlockIni(BaseNode *p){
	p->type = GetIndexType(p->indexId);
	switch(p->type){
	case TYPE_CHARS:
		p->keyLen = 256;
		p->KeyOffset = 10;
		p->TupleLen = 300;
		break;
	case TYPE_FLOAT:
		p->keyLen = 4;
		p->KeyOffset = 2;
		p->TupleLen = 13;
		break;
	case TYPE_INT:
		p->keyLen = 4;
		p->KeyOffset = 3;
		p->TupleLen = 15;
		break;
	}
	//if(p->isLeaf)
#ifdef DEBUG
	p->capacity = M - 1;
#endif // DEBUG
#ifdef NDEBUG
	p->capacity = (DATA_LEN / p->TupleLen) - 1;
#endif // NDEBUG
}

//------------------------functions of FindIndex------------------------
Address FindIndex(int tableId, int indexId, TKey key){
	int i, j;
	int blockId = GetRootBlockId(indexId);
	int offset;

	if(blockId == -1)
		Address(indexId, -1);

	blockId = FindLeafBlock(blockId, key);

	BaseNode *t = (BaseNode *)GetBlock(blockId);
	offset = FindKeyInLeaf(t, key);

	return Address(blockId, offset);
}

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

int FindKeyInNonleaf(BaseNode *t, TKey key){
	int i;
	for(i = 1; i < t->num; i++)
		if(TKey(t->Key(i), t->type) > key)
			break;
	return (i - 1);
}

int FindKeyInLeaf(BaseNode *t, TKey key){
	int i;
	for(i = 0; i < t->num; i++)
		if(TKey(t->Key(i), t->type) == key){
			return i;
		}
	return -1;
}

//------------------------functions of InsertIndex------------------------
Address InsertIndex(int tableId, int indexId, TKey key){
	int i, j;
	int blockId;	///< the target block ID
	int offset;		///< the offset of the new key in the target block
	BaseNode *p;
	int pb = GetRootBlockId(indexId);
	
	// if the index tree is empty
	if(pb == -1){
		pb = NewBlock();
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

		UpdateRootBlockId(indexId, pb);
		UpdateDataBlockId(indexId, pb);

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
		int qb = NewBlock();
		BaseNode *q = (BaseNode *)GetNewBlock(qb);
		*q = *p;
		q->blockId = qb;
		q->isLeaf = true;
		q->isRoot = false;
		q->parent = -1;
		q->num = 0;
		q->next = p->next;
		p->next = qb;

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
	
	if(i == -1 && !p->isRoot)
		UpdateParentKey((BaseNode *)GetBlock(p->parent),
			TKey(p->Key(1), p->type), TKey(p->Key(0), p->type));

	return (i + 1);
}

void InsertInParent(BaseNode *p, TKey key, BaseNode *q){
	int offset;
	int rb;
	BaseNode *r;

	// if p is the root, create a new root for p and q
	if(p->isRoot){
		rb = NewBlock();
		r = (BaseNode *)GetNewBlock(rb);
		*r = *p;
		r->blockId = rb;
		r->isLeaf = false;
		r->isRoot = true;
		//r->capacity = 4000/(r->keyLen+sizeof(int)) - 1;
		r->parent = r->next = -1;
		r->num = 2;
		r->WritePointer(0, p->blockId);
		r->WritePointer(1, q->blockId);
		r->WriteKey(0, p->Key(0));
		r->WriteKey(1, key.toData());

		p->isRoot = q->isRoot = false;
		p->parent = q->parent = rb;

		UpdateRootBlockId(r->indexId, rb);
		return;
	}
	
	// if p has a parent, try to insert in it
	rb = p->parent;
	r = (BaseNode *)GetBlock(rb);
	if(r->num < r->capacity){
		// If the parent's capacity is enough, insert into it
		offset = InsertInNonleaf(r, key);
		r->WritePointer(offset, q->blockId);
		q->parent = rb;
	}
	else{
		// If the parent is full, split it
		// create a new block to split
		int sb = NewBlock();
		BaseNode *s = (BaseNode *)GetNewBlock(sb);
		*s = *r;
		s->blockId = sb;
		s->num = 0;
		s->isLeaf = false;
		s->isRoot = false;
		s->parent = s->next = -1;

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

void CopyBlock(BaseNode *p, int ps, int len, BaseNode *q, int qs){
	for(int i  = 0; i < len; i++){
		q->WriteRecord(qs + i, p->Record(ps + i));
	}
}

//------------------------functions in DeleteIndex------------------------
Address DeleteIndex(int tableId, int indexId, TKey key){
	int pb = GetRootBlockId(indexId);

	if(pb == -1)
		throw ErIndexNotExist();

	pb = FindLeafBlock(pb, key);
	BaseNode *p = (BaseNode *)GetBlock(pb);
	return DeleteEntry(p, key);
}

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
				FreeBlock(pb);
				UpdateRootBlockId(p->indexId, -1);
				UpdateDataBlockId(p->indexId, -1);
				addr.offset = NOTFOUND;
			}
			return addr;
		}
		qb = DataToPointer(p->Pointer(0));
		q = (BaseNode *)GetBlock(qb);
		q->isRoot = true;
		q->parent = -1;
		FreeBlock(pb);
		UpdateRootBlockId(q->indexId, qb);

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
		FreeBlock(pb);

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
		FreeBlock(rb);

		// delete the entry in the parent node
		DeleteEntry(q, TKey(r->Key(0), r->type));

		return addr;
	}

	// the number of entries is too small, and unhandled
	throw ErUnknownError();
}

Address DeleteKey(BaseNode *p, TKey key){
	int offset;

	if(p->isLeaf)
		offset = FindKeyInLeaf(p, key);
	else
		offset = FindKeyInNonleaf(p, key);
	if(offset == -1 || TKey(p->Key(offset), p->type) != key)
		throw ErKeyNotFound(key);
	
	// update their parent's key
	if(!offset && !p->isRoot)
		UpdateParentKey((BaseNode *)GetBlock(p->parent),
			TKey(p->Key(0), p->type), TKey(p->Key(1), p->type));
	// delete the key
	p->num--;
	LeftShift(p, offset, 1);

	return Address(p->blockId, offset);
}

void UpdateParentKey(BaseNode *p, TKey oldKey, TKey newKey){
	int offset;

	offset = FindKeyInNonleaf(p, oldKey);
	p->WriteKey(offset, newKey.toData());
	if(offset == 0 && !p->isRoot){
		UpdateParentKey((BaseNode *)GetNewBlock(p->parent), oldKey, newKey);
	}
}

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

void RightShift(BaseNode *p, int start, int len){
	for(int i = start; i >= len; i--){
		p->WriteRecord(i, p->Record(i - len));
	}
}

//------------------------functions in DropIndex------------------------
void DropIndex(int tableId, int indexId){
	int i;
	int pb;
	BaseNode *p;
	queue<int> que;

	pb = GetRootBlockId(indexId);
	if(pb == -1){
		throw ErIndexNotExist();
	}
	
	que.push(pb);
	while(!que.empty()){
		pb = que.front();
		que.pop();
		p = (BaseNode *)GetBlock(pb);
		if(!p->isLeaf)
			for(i = 0; i < p->num; i++)
				que.push(DataToPointer(p->Pointer(i)));
		FreeBlock(pb);
	}

	UpdateRootBlockId(indexId, -1);
	UpdateDataBlockId(indexId, -1);
}
