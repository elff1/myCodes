#ifndef _RECORD_H
#define _RECORD_H

#include <vector>
#include "miniSQL.h"
#include "Index.h"
bool RcdSelect(SelectData);
bool RcdInsert( InsertData );
bool RcdDelete(DeleteData);
bool RcdCreateIndex(CreateIndexData);

class Tuple{
public:
	vector<TKey> tuple; 
};

Tuple CheckType(InsertData InDt);

Tuple CheckType(SelectData SlDt);

/*
choose the most suitable condition, including index and effective
first argument is the argument get directly from interpreter
second argument is the pointer to the active table
third argument is a pointer points to the best condition, the result. If no condition actually, return null
*/
template <class Type>
Condition *ChseBstCnd(Type &DltDt,TableInfo* TlIf, int &tag)  //choose best condition
{	
	tag = -1; //record the chosen condition

	if(DltDt.itemCount == 0)  //there is no condition
		return NULL;//Cnd = NULL;
	else
	{
		int i = 0;
		IndexInfo *IdIf =NULL;
		for(i=0; i < DltDt.itemCount;i++)
		{
			//find the first condition that has index, or the condition has index and the operation is equal
			IdIf = GetIndex(TlIf, DltDt.condition[i].keyName); 
			if(DltDt.condition[i].comptype == NOT_EQUAL)
				continue;
			if(IdIf&&(tag==-1) || IdIf&&(tag!=-1)&&(DltDt.condition[i].comptype == EQUAL))tag = i;   			
		}
		if(tag == -1/*i == DltDt.itemCount*/) //no key in condition has a index
			return NULL;//Cnd = NULL;
		else
			return &(DltDt.condition[tag]);//Cnd = &(DltDt.condition[tag]);

		//return tag;
	}
}  


/*
judge whether the data in block conforms the condition, if yes ,return true
first argument is the argument get directly from interpreter
second argument is the pointer to the active table
third argument is the pointer to the active block
forth argument is the offset of the active tuple
*/
template <class Type>
bool JudgeCnd(Type &SlctDt, TableInfo * TlIf, BaseNode *BsNd, int Offset) //judge the condition
{
	if(SlctDt.itemCount == 0) return true;
	//pretreatment
	int *CdtOffset;  //record the offset of every key in the conditions
	CdtOffset = (int *)malloc(SlctDt.itemCount*sizeof(int));
	int *CdtSize; //record the bytes need of every key
	CdtSize = (int *)malloc(SlctDt.itemCount*sizeof(int));
	for(int i=0; i < SlctDt.itemCount; i++)CdtOffset[i] = 0; 
	for(int i=0; i < SlctDt.itemCount; i++)CdtSize[i] = 0;
	//count the offset
	int BaseOffset = 0; //the total offset(bytes) of a tuple
	list<KeyInfo *>::iterator itr;
	for(itr = TlIf->keyInfoList.begin(); itr != TlIf->keyInfoList.end(); itr++)  //traversal the key list
	{
		for(int i=0; i<SlctDt.itemCount; i++) //compare the key name in catalog with every key in condition
		{ 
			//if(i == tag)continue;
			if(SlctDt.condition[i].keyName == (*itr)->keyName)
			{
				CdtOffset[i]=BaseOffset;          //count the offset
				CdtSize[i] = (*itr)->keySize;   //record the size of every key
				//break;
			}

		}
		BaseOffset+=(*itr)->keySize;
	}

	bool OkOrNot = true;  //whether the tuple conforms the conditions?
	for(int i=0; i<SlctDt.itemCount; i++) //traversal all condition
	{
		void* p = &(BsNd->data[Offset+CdtOffset[i]]);
		if(SlctDt.condition[i].dataType == TYPE_CHARS) //condition value is char type
		{
			
			int num = 0;
			string s("",CdtSize[i]);
			for(int j=0; j < CdtSize[i]; j++)
			{
				if(BsNd->data[Offset+CdtOffset[i]+j]==0)break;
				s[j] = BsNd->data[Offset+CdtOffset[i]+j];
				num++;
			}
			string ss("",num);
			for(int j=0; j < num;j++)
			{
				ss[j] = s[j];
			}

			switch(SlctDt.condition[i].comptype)
			{
			case LESS_THAN: {OkOrNot = OkOrNot & (ss < SlctDt.condition[i].dataValue);break;}
			case LESS_EQUAL: {OkOrNot = OkOrNot & (ss <= SlctDt.condition[i].dataValue);break;}
			case EQUAL: {OkOrNot = OkOrNot & (ss == SlctDt.condition[i].dataValue);break;}
			case GREATER_EQUAL: {OkOrNot = OkOrNot & (ss >= SlctDt.condition[i].dataValue);break;}
			case GREATER_THAN: {OkOrNot = OkOrNot & (ss > SlctDt.condition[i].dataValue);break;}
			case NOT_EQUAL: {OkOrNot = OkOrNot & (ss != SlctDt.condition[i].dataValue);break;}				   
			}
		}
		else if(SlctDt.condition[i].dataType == TYPE_FLOAT)
		{
			float vl1 = *((float*)p);   //get value as float type
			//change string to float
			float vl2;
			istringstream s;
			s.str(SlctDt.condition[i].dataValue);
			s >> vl2;
			//compare according to the operation
			switch(SlctDt.condition[i].comptype)
			{
			case LESS_THAN: {OkOrNot = OkOrNot & (vl1 < vl2);break;}
			case LESS_EQUAL: {OkOrNot = OkOrNot & (vl1 <= vl2);break;}
			case EQUAL: {OkOrNot = OkOrNot & (vl1 == vl2);break;}
			case GREATER_EQUAL: {OkOrNot = OkOrNot & (vl1 >= vl2);break;}
			case GREATER_THAN: {OkOrNot = OkOrNot & (vl1 > vl2);break;}
		    case NOT_EQUAL: {OkOrNot = OkOrNot & (vl1 != vl2);break;}
			}
		}
		else if(SlctDt.condition[i].dataType == TYPE_INT)
		{
			int vl1 = *((int*)p);   //get value as int type
			//change string to int
			int vl2;
			istringstream s;
			s.str(SlctDt.condition[i].dataValue);
			s >> vl2;
			//compare according to the operation
			switch(SlctDt.condition[i].comptype)
			{
			case LESS_THAN: {OkOrNot = OkOrNot & (vl1 < vl2);break;}
			case LESS_EQUAL: {OkOrNot = OkOrNot & (vl1 <= vl2);break;}
			case EQUAL: {OkOrNot = OkOrNot & (vl1 == vl2);break;}
			case GREATER_EQUAL: {OkOrNot = OkOrNot & (vl1 >= vl2);break;}
			case GREATER_THAN: {OkOrNot = OkOrNot & (vl1 > vl2);break;}
			case NOT_EQUAL: {OkOrNot = OkOrNot & (vl1 != vl2);break;}
			}

		}
	}
	if(OkOrNot)return true;
	else return false;
}

/*
search for the index built on the key
first argument is the pointer to the active table
second argument is the name of key
if there is no index, return null
*/
IndexInfo* GetIndex(TableInfo *, string);

/*







/*
output the suitable data of selection result
first argument is the pointer to the active table
second argument is the pointer to the active block
third argument is the offset of the active tuple
*/
void OutPut(TableInfo*, BaseNode*, int);

/*

*/
bool IfUnique(InsertData &InstDt, TableInfo * TlIf, Tuple &);

#endif _RECORD_H