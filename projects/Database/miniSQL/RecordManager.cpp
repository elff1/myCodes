#ifndef _RECORDMANAGER_CPP
#define _RECORDMANAGER_CPP

#include "miniSQL.h"
#include"Interpreter.h"
#include "CatalogManager.h"
#include "Buffer.h"
#include "Index.h"
#include "RecordManager.h"
#include <cstdlib>
#include <iostream>
#include "test.h"
extern CatalogInfo catalogInfo;
using namespace std;

template<class Type>
void GetType(Type &SltDt)   //get the type of every condition value
{
	TableInfo * TlIf = catalogInfo.FindTable(SltDt.tableName);
	for(int i = 0; i < SltDt.itemCount; i++)
	{
		SltDt.condition[i].dataType = (TlIf->FindKey(SltDt.condition[i].keyName))->keyType;
	}
}

Tuple CheckType(InsertData InDt)
{
	Tuple result;
	TableInfo* TlIf;
	//if(catalogInfo.FindTable(InDt.tableName) == NULL) throw(*(new ErUnknownTable) );
   //check whether the table is exist
	if(catalogInfo.FindTable(InDt.tableName) == NULL)
		throw ErUnknownTable();
	TlIf = catalogInfo.FindTable(InDt.tableName);

    //check whether the input value is right
	if(TlIf->keyInfoList.size() != InDt.itemCount)
		throw ErWrongKeyNum();
	
	ListKeyInfo::iterator itr;
	int i;
	for(itr = TlIf->keyInfoList.begin(), i = 0; itr!=TlIf->keyInfoList.end(); i++, itr++)
	{
		switch((*itr)->keyType){
		case TYPE_INT:
			{
				if((InDt.dataType[i] & BIT_INT) == 0)
					throw ErWrongType(TKey(InDt.dataValue[i]));
				result.tuple.push_back(TKey(atoi(InDt.dataValue[i].data())));
				break;}
		case  TYPE_FLOAT:
			{
				if((InDt.dataType[i] & BIT_FLOAT) == 0)
					throw ErWrongType(TKey(InDt.dataValue[i]));
				result.tuple.push_back(TKey(float(atof(InDt.dataValue[i].data()))));
				break;
			}
		case TYPE_CHARS:
			{
				if((InDt.dataType[i] & BIT_CHARS) == 0)
					throw ErWrongType(TKey(InDt.dataValue[i]));
	
				if(InDt.dataValue[i].length() >= (*itr)->keySize)
					throw ErTooLongAttr();
				result.tuple.push_back(TKey(InDt.dataValue[i].data()));
				break;
			}
		}
	}

	return result;
}

Tuple CheckType(SelectData SlDt)
{
	Tuple result;
	TableInfo* TlIf;
	//if(catalogInfo.FindTable(InDt.tableName) == NULL) throw(*(new ErUnknownTable) );
	//check whether the table is exist
	if(catalogInfo.FindTable(SlDt.tableName) == NULL)
		throw ErUnknownTable();

	TlIf = catalogInfo.FindTable(SlDt.tableName);

	//when index is empty
	if(!TlIf->isEmpty )
		throw ErEmptyQuery();

	//check whether the keys are exist
	for(int j=0; j<SlDt.itemCount; j++)
	{
		bool isExist = false;
		if(TlIf->FindKey(SlDt.condition[j].keyName) )
			isExist = true;
		if(!isExist)
			throw ErUnknownKey();
	}
	

	ListKeyInfo::iterator itr;
	int i;
	for(i = 0; i < SlDt.itemCount; i++){
		switch(TlIf->FindKey(SlDt.condition[i].keyName)->keyType){
		case TYPE_INT:
			{
				if((SlDt.condition[i].dataType & BIT_INT) == 0)
					throw ErWrongType(TKey(SlDt.condition[i].dataValue));
				result.tuple.push_back(TKey(atoi(SlDt.condition[i].dataValue.data())));
				break;}
		case  TYPE_FLOAT:
			{
				if((SlDt.condition[i].dataType & BIT_FLOAT) == 0)
					throw ErWrongType(TKey(SlDt.condition[i].dataValue));
				result.tuple.push_back(TKey(float(atof(SlDt.condition[i].dataValue.data()))));
				break;
			}
		case TYPE_CHARS:
			{
				if((SlDt.condition[i].dataType & BIT_CHARS) == 0)
					throw ErWrongType(TKey(SlDt.condition[i].dataValue));
				
				if(SlDt.condition[i].dataValue.length() >= TlIf->FindKey(SlDt.condition[i].keyName)->keySize)/*(*itr)->keySize*/
					throw ErWrongType(TKey(SlDt.condition[i].dataValue));
				result.tuple.push_back(TKey(SlDt.condition[i].dataValue));
				break;
			}
		}
	}

	return result;
}

Tuple CheckType(DeleteData DltDt)
{
	Tuple result;

	TableInfo* TlIf ;

	//check whether the table is exist
	if(catalogInfo.FindTable(DltDt.tableName) == NULL)
		throw ErUnknownTable();

	TlIf = catalogInfo.FindTable(DltDt.tableName);

	if(!TlIf->isEmpty)
		throw ErEmptyQuery();

	//check whether the keys are exist
	for(int j=0; j<DltDt.itemCount; j++)
	{
		bool isExist = false;
		if(TlIf->FindKey(DltDt.condition[j].keyName))
			isExist = true;
		if(!isExist)
			throw ErUnknownKey();
	}


	ListKeyInfo::iterator itr;
	int i;
	for(i = 0; i < DltDt.itemCount; i++){
		switch(TlIf->FindKey(DltDt.condition[i].keyName)->keyType){
		case TYPE_INT:
			{
				if((DltDt.condition[i].dataType & BIT_INT) == 0)
					throw ErWrongType(TKey(DltDt.condition[i].dataValue));
				result.tuple.push_back(TKey(atoi(DltDt.condition[i].dataValue.data())));
				break;}
		case  TYPE_FLOAT:
			{
				if((DltDt.condition[i].dataType & BIT_FLOAT) == 0)
					throw ErWrongType(TKey(DltDt.condition[i].dataValue));
				result.tuple.push_back(TKey(float(atof(DltDt.condition[i].dataValue.data()))));
				break;
			}
		case TYPE_CHARS:
			{
				if((DltDt.condition[i].dataType & BIT_CHARS) == 0)
					throw ErWrongType(TKey(DltDt.condition[i].dataValue));
				if(DltDt.condition[i].dataValue.length() >= TlIf->FindKey(DltDt.condition[i].keyName)->keySize)
					throw ErWrongType(TKey(DltDt.condition[i].dataValue));
				result.tuple.push_back(TKey(DltDt.condition[i].dataValue));
				break;
			}
		}
	}

	return result;
}

IndexInfo* GetIndex(TableInfo *TlIf, string KeyName)  //search for the index built on the key
{
	ListIndexInfo::iterator itr;
	for(itr = TlIf->indexInfoList.begin(); itr != TlIf->indexInfoList.end(); itr++)
	{
		KeyInfo *temp = (KeyInfo *)((*itr)->indexKey);

		if(temp->keyName == KeyName)
			return *itr;
	}
	return NULL;
}

bool RcdCreateIndex(CreateIndexData CrtIndx)
{
	//get block as source data
	CatalogInfo &CtIf = catalogInfo;
	TableInfo *TbIf = CtIf.FindTable(CrtIndx.tableName);
	IndexInfo *IdIfp = TbIf->FindIndex(TbIf->primaryKey->keyID); //get index information by primary key(for first block)
	IndexInfo *IdIfn = TbIf->FindIndex(CrtIndx.indexName);      //get index information by index name given(for insertion)
	//count the offset of the key to be created index
	ListKeyInfo::iterator itr;
	int Keyoffset=0;
	for(itr = TbIf->keyInfoList.begin(); itr != TbIf->keyInfoList.end(); itr++)
	{
		if((*itr)->keyName == CrtIndx.keyName)break;
		Keyoffset+=(*itr)->keySize;
	}
	int Block = IdIfp->dataBlockID;  //get first block id
	BaseNode *BsNd = GetBlock(Block);  //get first block address
	//get the value of key to be created index
	while(BsNd != NULL)
	{
		Address Add;
		for(int i=0; i<(BsNd->num * BsNd->TupleLen); i+= BsNd->TupleLen)  //traversal every tuple
		{
			if(TbIf->primaryKey->keyType == TYPE_CHARS)
			{
				string str("",TbIf->primaryKey->keySize);
				for(unsigned int j=0; j<TbIf->primaryKey->keySize; j++)
				{
					str[j]=BsNd->data[i+BsNd->KeyOffset+j];
				}
				Add = InsertIndex(TbIf->tableID, IdIfn->indexID, *(new TKey(str)));//get address of block to be inserted
			}
			else if(TbIf->primaryKey->keyType == TYPE_FLOAT)
			{
				void*p = &(BsNd->data[i+BsNd->KeyOffset]);
				float f1 = *((float*)p);
				Add = InsertIndex(TbIf->tableID, IdIfn->indexID,*(new TKey(f1)) );
			}
			else if(TbIf->primaryKey->keyType == TYPE_INT)
			{
				void*p = &(BsNd->data[i+BsNd->KeyOffset]);
				int f1 = *((int*)p);
				Add = InsertIndex(TbIf->tableID, IdIfn->indexID, *(new TKey(f1)) );
			}
			
			BaseNode *BsNdd = GetBlock(Add.blockId); //get block to insert
			//start writing
			for(int j=0; j < BsNd->TupleLen; j++)
			{
				BsNdd->data[Add.offset+j] = BsNd->data[i+j]; 
			}
			BsNdd->TupleLen = BsNd->TupleLen; //update tuple length
			BsNdd->KeyOffset = Keyoffset; //update the offset in every tuple
		}
		BsNd = GetBlock(BsNd->next);
	}	
	return true;
}

bool RcdDelete(DeleteData DltDt)
{
	Tuple result = CheckType(DltDt);
	CatalogInfo &Ctlg = catalogInfo;
	TableInfo *TlIf = Ctlg.FindTable(DltDt.tableName);  //get the active table
	Condition *Cnd = NULL;

	GetType(DltDt);

	int offsetNum;
	Cnd = ChseBstCnd(DltDt, TlIf, offsetNum); //get best condition

	int TotalNum = 0;  //count the total number of deleted tuple
	string AcIdxNm;  //store the active index(if there is one)
	Address Addrs, tmpAddr;  //store the FindIndex result(for equal situation)
	//set loop condition according to condition returned
	//BaseNode * StrNd = NULL, *EndNd = NULL;	
	int strId = -1, endId = -1, nextEnd = -1;
	IndexInfo *IdIf;
	if(Cnd == NULL)
	{
		IdIf = GetIndex(TlIf,TlIf->primaryKey->keyName); //get the index information of primary key
		AcIdxNm = IdIf->indexName;  //get the name of active index for afterward steps 
		/*ListIndexInfo::iterator itr;
		for(itr = TlIf->indexInfoList.begin(); itr != TlIf->indexInfoList.end(); itr++)
		{
			KeyInfo * temp = (KeyInfo*)((*itr)->indexKey);
			if(temp->keyID == TlIf->primaryKey->keyID)
				break;
		}*/
		//BaseNode * BsNd0 = GetBlock((*itr)->dataBlockID); //the first block of data on primary key
		int blockId = IdIf->dataBlockID;
		strId = blockId;
		endId = -1;
		nextEnd = -1;
	}
	else
	{
		IdIf = GetIndex(TlIf, Cnd->keyName); //get the index on the condition
		AcIdxNm = IdIf->indexName;  //get the name of active index for afterward steps
		Address Add = FindIndex(TlIf->tableID, IdIf->indexID, TKey(result.tuple.at(offsetNum)));// *(new TKey(Cnd->dataValue)));  
		Addrs = Add;  //get the address for afterward steps
		//BaseNode *BsNd0 = GetBlock(IdIf->dataBlockID); //get the first block of data of the index
		BaseNode *BsNd1 = GetBlock(Add.blockId);     //get the block of the key
		BaseNode *BsNd2 = GetBlock(BsNd1->next);   //get the next block of the key
		int blockId0 = IdIf->dataBlockID;
		int blockId1 = Add.blockId;
		int blockId2 = BsNd1->next;
		int blockId3;
		if(BsNd2)
		 blockId3= BsNd2->next;
		else 
			blockId3 = -1;

		//different condition operation
		switch (Cnd->comptype)
		{
		case EQUAL:
			{
				strId = blockId1;
				endId = blockId2;
				nextEnd = blockId3;
				break;
			}
		case LESS_THAN:
			{
				strId = blockId0;
				endId = blockId2;
				nextEnd = blockId3;
				break;
			}
		case LESS_EQUAL:
			{
				strId = blockId0;
				endId = blockId2;
				nextEnd = blockId3;
				break;
			}
		case GREATER_THAN:
			{
				strId = blockId1;
				endId = -1;
				break;
			}
		case GREATER_EQUAL:
			{
				strId = blockId1;
				endId = -1;
				break;
			}
		case NOT_EQUAL:
			{
				strId = blockId0;
				endId = -1;
				break;
			}
		}
	}

	//select the tuple conforms the condition to delete
	//BaseNode *BsNd = StrNd;
	int BsId = strId;
	int SrtOffset = 0;    //the offset start to seek data
	//if(Cnd != NULL&&Cnd->comptype == EQUAL) SrtOffset = Addrs.offset;  //when equal situation
	BaseNode * BsNd = GetBlock(BsId);
	while(BsId != endId)
	{
		
		int i = 0;
		int t = (BsNd->TupleLen)*(BsNd->num);
		Address ReDone;   //return data for normal index
		for(i= SrtOffset * BsNd->TupleLen; i<(BsNd->TupleLen)*(BsNd->num);i+=BsNd->TupleLen)  //traversal every tuple
		{
			if(JudgeCnd(DltDt, TlIf, BsNd, i))  //conform the condition
			{
				TotalNum++; //counter
				//traversal all the index
				ListIndexInfo::iterator itrr;
				//Address ReDone;   //return data for normal index
				IndexInfo *indexPtrCur;  

				for(itrr = TlIf->indexInfoList.begin(); itrr != TlIf->indexInfoList.end();itrr++) //traversal  to get the information of every index
				{
					
					if((*itrr)->indexName == AcIdxNm)
					{
						indexPtrCur = *itrr;
						continue;
					}
					if((*itrr)->dataBlockID == NOT_FOUND)
						throw ErIndexNotExist();
					BaseNode *p = GetBlock((*itrr)->dataBlockID);
					if(p == NULL)
						throw ErDataBlockNotExist();
					
					TKey key(BsNd->data + i + p->KeyOffset, p->type);

					DeleteIndex(TlIf->tableID, (*itrr)->indexID, key);//TKey(BsNd->data + i + cnt, temp->keyType));
					//if(AcIdxNm == (*itrr)->indexName)
						//ReDone = tmpAddr;
				}
				
				if(indexPtrCur->dataBlockID == NOT_FOUND)
					throw ErIndexNotExist();
				BaseNode *p = GetBlock(indexPtrCur->dataBlockID);
				if(p == NULL)
					throw ErDataBlockNotExist();

				TKey key(BsNd->data + i + p->KeyOffset, p->type);
				
				ReDone = DeleteIndex(TlIf->tableID, indexPtrCur->indexID, key);

				//if(ReDone.offset == -1)
				//	break;


				if(ReDone.blockId == BsId) 
				{
					SrtOffset = ReDone.offset;
					break;
				}
				else if(ReDone.blockId == endId)
				{
					BsId = endId;
					endId = GetBlock(endId)->next;
					if(nextEnd != -1)
					    nextEnd = GetBlock(endId)->next;
					BsNd = GetBlock(ReDone.blockId);
					SrtOffset = ReDone.offset;
				    break;
				}
				else
				{
					BsId = ReDone.blockId;
					BsNd = GetBlock(ReDone.blockId);
					SrtOffset = ReDone.offset;
					break;
				}
				if(!catalogInfo.IsBlockUsed(endId))
				{
					BsId = ReDone.blockId;
					endId = nextEnd;
					if(nextEnd != -1)
					    nextEnd = GetBlock(nextEnd)->next;
					BsNd = GetBlock(ReDone.blockId);
					SrtOffset = ReDone.offset;
					break;
				}
				//if(ReDone.offset == -1)
				
			}
		}
		//if(Cnd != NULL && Cnd->comptype == EQUAL)break;
		
		if(i == t)
		{
			BsId = BsNd->next;
			BsNd =  GetBlock(BsNd->next);
		}
		if(ReDone.offset == -1)
			break;
	}
	
	if(TotalNum == 0)
		printf("No tuple is deleted\n");
	else if(TotalNum == 1)
		printf("Delete %d tuple\n", TotalNum);
	else
		printf("Delete %d tuples\n", TotalNum);

	return true;  
}

bool RcdInsert(InsertData InstDt)
{
	//CheckType(InstDt);
	//get all the index in the table
	CatalogInfo &Ctlg=catalogInfo;

	Tuple result = CheckType(InstDt);

	TableInfo *TlIf =Ctlg.FindTable(InstDt.tableName);
	//count the total size of a tuple
	ListKeyInfo::iterator itrr;
	int ttlSize = 0;
	for(itrr = TlIf->keyInfoList.begin(); itrr != TlIf->keyInfoList.end(); itrr++)
	{
		ttlSize +=(*itrr)->keySize;
	}

	if(!IfUnique(InstDt,TlIf, result))
	{
		throw ErDupColumn();
		return false;
	}

	ListIndexInfo::iterator itr;
	//insert in index 
	for(itr = TlIf->indexInfoList.begin(); itr != TlIf->indexInfoList.end(); itr++)
	{
		int cnt = 0; //count the position of the key
		int cntSize =0; //count the offset of the key
		KeyInfo *temp;
		temp = (KeyInfo *)((*itr)->indexKey);

		ListKeyInfo::iterator itrr;
		for(itrr = TlIf->keyInfoList.begin(); itrr != TlIf->keyInfoList.end(); itrr++)
		{
			if(temp->keyName == (*itrr)->keyName)
				break;

			cnt++;
			cntSize+=(*itrr)->keySize;
		}
		Address Add;
		TKey key = result.tuple.at(cnt);
		try{
			Add = InsertIndex(TlIf->tableID, (*itr)->indexID, key);//get block information from index
		}
		catch (ErTest &e){
			cout << temp->keyName << ': ' << key << endl;
			throw;
		}
		BaseNode *BsNd = GetBlock(Add.blockId);
		//BsNd->KeyOffset = cntSize;//update
		//BsNd->TupleLen = ttlSize;
		BsNd->dirty = true;
		//start writing
 		ListKeyInfo::iterator it;
		it = TlIf->keyInfoList.begin();
		int cntt = Add.offset * BsNd->TupleLen;  //the offset of value in tuple
		ListKeyInfo::iterator itrkey;
		int i=-1;  //tag for the position of key

		for(itrkey = TlIf->keyInfoList.begin(); itrkey != TlIf->keyInfoList.end(); itrkey++,it++)
		{
			i++;

			switch((*itrkey)->keyType)
			{
			case TYPE_CHARS:
				{
					unsigned int j;
					for(j = 0; j<(*it)->keySize; j++)
					{
						BsNd->data[cntt] = result.tuple.at(i).toData()[j];// InstDt.dataValue[i].data()[j];
						//printf("%c",BsNd->data[cntt]);
						cntt++;
						if(InstDt.dataValue[i].data()[j] == '\0')
							break;
					}
					for(int k = j + 1; k < (*it)->keySize; k++)
					{
						cntt++;
					}
					//BsNd->WriteKey(cntt, result.tuple.at(i).toData());
					//cntt += (*it)->keySize;					
				}
				break;
			case TYPE_FLOAT:
				{
					float f = result.tuple.at(i).fKey;
					//printf("%f ", f);
					*((float*)(&(BsNd->data[cntt]))) = f;
					
					void *p;
					p = &(BsNd->data[cntt]);
					//printf("%f", *((float*)p));
					cntt+=(*it)->keySize;
				}
				break;
			case TYPE_INT:
				{
					int f = result.tuple.at(i).iKey;
					//printf("%d", f);
					*((int*)(&(BsNd->data[cntt]))) = f;

					void *p;
					p = &(BsNd->data[cntt]);
					//printf("%d", *((int*)p));
					cntt+=(*it)->keySize;
				}
				break;

			}
		}
	}
// 	KeyInfo * b = TlIf->primaryKey;
// 	IndexInfo * a = GetIndex(TlIf, b->keyName);
// 	PrintIndex(a->rootBlockID);
	printf("Insert 1 tuple\n");

	return true;
}

bool RcdSelect(SelectData SltDt)
{
	//CheckType(SltDt);
	Tuple result = CheckType(SltDt);
	GetType(SltDt);
	CatalogInfo &Ctlg = catalogInfo;
	TableInfo *TlIf = Ctlg.FindTable(SltDt.tableName);  //get the active table
	Condition *Cnd = NULL;
	int Counter = 0; //counter for the number of tuples being selected

	//printf("%s ")

	
	int offsetNum;
	Cnd = ChseBstCnd(SltDt, TlIf, offsetNum); //get best condition

	string AcIdxNm;  //store the active index(if there is one)
	Address Addrs;  //store the FindIndex result(for equal situation)
	//set loop condition according to condition returned
	//BaseNode * StrNd = NULL, *EndNd = NULL;	
	int strId = -1, endId = -1;
	if(Cnd == NULL)
	{
		IndexInfo *IdIf = GetIndex(TlIf,TlIf->primaryKey->keyName); //get the index information of primary key
		AcIdxNm = IdIf->indexName;  //get the name of active index for afterward steps 
		//BaseNode * BsNd0 = GetBlock(IdIf->dataBlockID);//(*itr)->dataBlockID); //the first block of data on primary key
		int blockId0 = IdIf->dataBlockID;
		strId = blockId0;
		endId = -1;
		//StrNd = BsNd0;
		//EndNd = NULL;
	}
	else
	{
		IndexInfo *IdIf = GetIndex(TlIf, Cnd->keyName); //get the index on the condition
		AcIdxNm = IdIf->indexName;  //get the name of active index for afterward steps
		Address Add = FindIndex(TlIf->tableID, IdIf->indexID, TKey(result.tuple.at(offsetNum)));  
		Addrs = Add;  //get the address for afterward steps
		//BaseNode *BsNd0 = GetBlock(IdIf->dataBlockID); //get the first block of data of the index
		BaseNode *BsNd1 = GetBlock(Add.blockId);     //get the block of the key
		//BaseNode *BsNd2 = GetBlock(BsNd1->next);   //get the next block of the key
		int blockId0 = IdIf->dataBlockID;
		int blockId1 = Add.blockId;
		int blockId2 = BsNd1->next;

		//different condition operation
		switch (Cnd->comptype)
		{
		case EQUAL:
			{
				strId = blockId1;
				endId = blockId2;
				break;
			}
		case LESS_THAN:
			{
				strId = blockId0;
				endId = blockId2;
				break;
			}
		case LESS_EQUAL:
			{
				strId = blockId0;
				endId = blockId2;
				break;
			}
		case GREATER_THAN:
			{
				strId = blockId1;
				endId = -1;
				break;
			}
		case GREATER_EQUAL:
			{
				strId = blockId1;
				endId = -1;
				break;
			}
		case NOT_EQUAL:
			{
				strId = blockId0;
				endId = -1;
				break;
			}
		}
	}

	//select the tuple conforms the condition to delete
	//BaseNode *BsNd = StrNd;
	int BsId = strId;
	int SrtOffset = 0;    //the offset start to seek data
	//if(Cnd!=NULL&&Cnd->comptype == EQUAL)
		//SrtOffset = Addrs.offset*BsNd->TupleLen;  //when equal situation, pay attation

	ListKeyInfo::iterator www;
	for(www = TlIf->keyInfoList.begin(); www != TlIf->keyInfoList.end(); www++)
		cout<< (*www)->keyName <<'\t'<<' ';
	printf("\n");

	while(BsId != endId)
	{
		BaseNode * BsNd = GetBlock(BsId);    //get active block
		int i;
		for(i= SrtOffset; i<(BsNd->TupleLen)*(BsNd->num);i+=BsNd->TupleLen)  //traversal every tuple
		{
			if(JudgeCnd(SltDt, TlIf, BsNd, i))  //conform the condition
			{
				Counter++;
				OutPut(TlIf, BsNd, i);
				//if(Cnd!= NULL&&Cnd->comptype == EQUAL)
					//break;				
			}
		}
		//if(Cnd!=NULL&&Cnd->comptype == EQUAL)
			//break;
		BsId = BsNd->next;
		//BsNd =  GetBlock(BsNd->next);
		
	}
	if(Counter == 0)
		printf("No tuple is chosen\n");
	else if(Counter == 1)
		printf("Select %d tuple\n", Counter);
	else
		printf("Select %d tuples\n", Counter);

	return true;  
}

void OutPut(TableInfo *TlIf, BaseNode *BsNd, int Offset)  //output the selection result
{
	ListKeyInfo::iterator itr;
	for(itr = TlIf->keyInfoList.begin(); itr != TlIf->keyInfoList.end(); itr++)
	{
		//output data itr->keySize
		char * p = NULL; //pointer for getting value string
		p = &(BsNd->data[Offset]); //get the address of value string

		if((*itr)->keyType == TYPE_CHARS)  //type is char
		{
			//get char[0] char[1]...one by one
			string s("",(*itr)->keySize);
			int num = 0;
			for(int i = 0; i < (*itr)->keySize; i++)
			{
				
				s[i] = BsNd->data[Offset + i];
				num ++;
				if(BsNd->data[Offset+i] == 0)
					break;
			}	
			char *c = (char *)malloc(num);
			for(int i =0 ; i < num; i++)
			{
				c[i] = s[i];
			}
		
			printf("%s\t", c);
			printf(" ");
		}
		else if((*itr)->keyType == TYPE_FLOAT) //type is float
		{
			printf("%f\t", *((float*)p));
			printf(" ");
		}
		else if((*itr)->keyType == TYPE_INT) //type is int
		{
			printf("%d\t", *((int*)p));
			printf(" ");
		}

		Offset += (*itr)->keySize;

	}
	printf("\n");
}

bool IfUnique(InsertData &InstDt, TableInfo * TlIf, Tuple &result)
{
	bool okOrNot = true;
	int num=0;

	ListIndexInfo::iterator itr;
	for(itr = TlIf->indexInfoList.begin(); itr != TlIf->indexInfoList.end(); itr++)
	{
		KeyInfo *key;
		
		key = (KeyInfo *)((*itr)->indexKey);
		num = 0;
		ListKeyInfo::iterator itrr;
		for(itrr = TlIf->keyInfoList.begin(); itrr != TlIf->keyInfoList.end(); itrr++)
		{
			if(key->keyName == (*itrr)->keyName)
				break;
			num ++;
		}
		Address add = FindIndex(TlIf->tableID, (*itr)->indexID, result.tuple.at(num));// InstDt.dataValue[num]);
		if(add.offset != NOT_FOUND)
			okOrNot = false;
	}
	return okOrNot;

}

#endif