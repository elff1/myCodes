#ifndef _CATALOGMANAGER_H_
#define _CATALOGMANAGER_H_

#include <list>
#include <string>
#include "miniSQL.h"
#include "Interpreter.h"
#include "Index.h"
using namespace std;

typedef list<int> ListInt;

int  GenerateID();
void FreeID(int deleteID);

class IndexInfo
{
public:
	class KeyInfo;
	class TableInfo;

	int indexID;            //the ID of the index
	
	int dataBlockID;        //the address of the first leaf node
	int rootBlockID;        //the address of the root node
	KeyInfo *indexKey;      //the pointer to the key of the index
	string indexName;       //the name of the index
	string indexKeyName;    //the name of the key of the index
	string indexTableName;  //the name of the table that the index belongs to
	TableInfo *indexTable;  //the table that the index belongs to

	IndexInfo()
	{

	}
};

class KeyInfo
{
public:
	int keyID;           //the ID of the key

	bool isUnique;         //whether this key needs to be unique
	DataType keyType;      //the data type of the key
	size_t keySize;        //the number of bytes needed to store this key
	string keyName;        //the name of the key

	KeyInfo()
	{

	}
};

typedef list<IndexInfo *> ListIndexInfo;
typedef list<KeyInfo *> ListKeyInfo;
class TableInfo
{
public:
	int tableID;              //the ID of the table
	
	bool isEmpty;                 //whether the table is empty
	//int dataBlockID;          //the address of the first leaf node
	//int rootBlockID;          //the address of the root node
	KeyInfo *primaryKey;          //the pointer to the primary key in 'keyInfoList'
	ListKeyInfo keyInfoList;      //the keys in the table
	int keyCount;                 //the number of items in the list 'keyInfoList'
	ListIndexInfo indexInfoList;  //the indices defined over this table
	int indexCount;               //the number of items in the list 'indexCount'
	string primaryKeyName;        //the name of primary key
	string tableName;             //the name of the table

	TableInfo()
	{
		keyInfoList.clear();
		keyCount = 0;
		indexInfoList.clear();
		indexCount = 0;
	}

	//returns the data structure recording the key information
	//returns NULL when not found
	KeyInfo* FindKey(int keyID)
	{
		ListKeyInfo::iterator it;

		for(it = keyInfoList.begin(); it != keyInfoList.end(); it++)
		{
			if((*it)->keyID == keyID)
			{
				return (*it);
			}
		}
		return NULL;
	}

	KeyInfo* FindKey(string keyName)
	{
		ListKeyInfo::iterator it;

		for(it = keyInfoList.begin(); it != keyInfoList.end(); it++)
		{
			if((*it)->keyName == keyName)
			{
				return (*it);
			}
		}
		return NULL;
	}

	void DropKey(int keyID)
	{
		ListKeyInfo::iterator it;

		for(it = keyInfoList.begin(); it != keyInfoList.end(); it++)
		{
			if((*it)->keyID == keyID)
			{
				FreeID((*it)->keyID);
				delete (*it);
				keyInfoList.erase(it);
				keyCount--;
			}
		}
	}

	void DropKey(string keyName)
	{
		ListKeyInfo::iterator it;

		for(it = keyInfoList.begin(); it != keyInfoList.end(); it++)
		{
			if((*it)->keyName == keyName)
			{
				FreeID((*it)->keyID);
				delete (*it);
				keyInfoList.erase(it);
				keyCount--;
			}
		}
	}
	//returns the data structure recording the index information
	//returns NULL when not found
	IndexInfo* FindIndex(int indexID)
	{
		ListIndexInfo::iterator it;

		for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
		{
			if((*it)->indexID == indexID)
			{
				return (*it);
			}
		}
		return NULL;
	}

	IndexInfo* FindIndex(string indexName)
	{
		ListIndexInfo::iterator it;

		for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
		{
			if((*it)->indexName == indexName)
			{
				return (*it);
			}
		}
		return NULL;
	}

	IndexInfo *CreateIndex(CreateIndexData &object)
	{
		//IndexInfo *newIndex;
		//KeyInfo *indexKey;

		//indexKey = FindKey(object.keyName);
		//if(indexKey == NULL)
		//{
		//	cout<<"The specified key doesn't exist in the table."<<endl;
		//	return NULL;
		//}

		//newIndex = FindIndex(object.indexName);
		//if(newIndex != NULL)
		//{
		//	cout<<"An index with the same name already exists."<<endl;
		//	return newIndex;
		//}

		//newIndex = new IndexInfo();
		//newIndex->dataBlockID = NOT_FOUND;
		//newIndex->indexID = GenerateID();
		//newIndex->indexKey = (IndexInfo::KeyInfo *)indexKey;
		//newIndex->indexKeyName = object.keyName;
		//newIndex->indexName = object.indexName;
		//newIndex->indexTable = (IndexInfo::TableInfo *)this;
		//newIndex->indexTableName = object.tableName;
		//newIndex->rootBlockID = NOT_FOUND;
		//indexInfoList.push_back(newIndex);
		//indexCount++;
		//cout<<"The index \""<<object.indexName<<"\" is successfully created."<<endl;

		KeyInfo *newKey;
		ListIndexInfo::iterator it;

		newKey = FindKey(object.keyName);

		if(object.keyName == primaryKeyName)
		{
			cout<<"Cannot create index on primary key."<<endl;
			return NULL;
		}

		if(newKey->isUnique == false)
		{
			cout<<"ERROR:Cannot create key on a non-unique key."<<endl;
			return NULL;
		}

		for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
		{
			if((*it)->indexKeyName == object.keyName)
			{
				if((*it)->indexName == object.indexName)
				{
					cout<<"An index with the same name already exists."<<endl;
				}
				else
				{
					(*it)->indexName = object.indexName;
					cout<<"The index \""<<object.indexName<<"\" is successfully created."<<endl;
				}
				return (*it);
			}
		}

		return NULL;
	}

	void DropIndex(int indexID)
	{
		ListIndexInfo::iterator it;
		extern void DropIndex(int tableID, int indexID);

		for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
		{
			if((*it)->indexID == indexID)
			{
				DropIndex(tableID, indexID);
				FreeID((*it)->indexID);
				delete (*it);
				indexInfoList.erase(it);
				indexCount--;
			}
		}
	}

	void DropIndex(string indexName)
	{
		ListIndexInfo::iterator it;
		extern void DropIndex(int tableID, int indexID);

		for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
		{
			if((*it)->indexName == indexName)
			{
				DropIndex(tableID, (*it)->indexID);
				FreeID((*it)->indexID);
				delete (*it);
				indexInfoList.erase(it);
				indexCount--;
			}
		}
	}

	void Dispose()
	{
		extern void DropIndex(int tableID, int indexID);

		for(ListIndexInfo::iterator i = indexInfoList.begin(); i != indexInfoList.end(); i++)
		{
			DropIndex(tableID, (*i)->indexID);
			FreeID((*i)->indexID);
			delete (*i);
		}
		indexInfoList.clear();
		indexCount = 0;

		for(ListKeyInfo::iterator i = keyInfoList.begin(); i != keyInfoList.end(); i++)
		{
			FreeID((*i)->keyID);
			delete (*i);
		}
		keyInfoList.clear();
		keyCount = 0;
	}
};

typedef list<TableInfo *> ListTableInfo;
class CatalogInfo
{
public:
	ListInt emptyBlockList;          //the IDs of the blocks available for writing
	int emptyBlockCount;             //the number of items in the list 'emptyBlockIDList'
	//ListIndexInfo indexInfoList;     //the indices in the database
	//int indexCount;                  //the number of items in the list 'indexInfoList'
	ListTableInfo tableInfoList;     //the tables in the database
	int tableCount;

	CatalogInfo()
	{
		emptyBlockList.clear();
		emptyBlockCount = 0;
		//indexInfoList.clear();
		//indexCount = 0;
		tableInfoList.clear();
		tableCount = 0;
	}
	//returns the data structure recording the index information
	//returns NULL when not found
	//IndexInfo* FindIndex(int indexID)
	//{
	//	ListIndexInfo::iterator it;

	//	for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
	//	{
	//		if((*it)->indexID == indexID)
	//		{
	//			return (*it);
	//		}
	//	}
	//	return NULL;
	//}

	//IndexInfo* FindIndex(string indexName)
	//{
	//	ListIndexInfo::iterator it;

	//	for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
	//	{
	//		if((*it)->indexName == indexName)
	//		{
	//			return (*it);
	//		}
	//	}
	//	return NULL;
	//}

	//void DropIndex(int indexID)
	//{
	//	ListIndexInfo::iterator it;

	//	for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
	//	{
	//		if((*it)->indexID == indexID)
	//		{
	//			FreeID((*it)->indexID);
	//			delete (*it);
	//			indexInfoList.erase(it);
	//			indexCount--;
	//		}
	//	}
	//}

	//void DropIndex(string indexName)
	//{
	//	ListIndexInfo::iterator it;

	//	for(it = indexInfoList.begin(); it != indexInfoList.end(); it++)
	//	{
	//		if((*it)->indexName == indexName)
	//		{
	//			FreeID((*it)->indexID);
	//			delete (*it);
	//			indexInfoList.erase(it);
	//			indexCount--;
	//		}
	//	}
	//}

	TableInfo* FindTable(int tableID)
	{
		ListTableInfo::iterator it;

		for(it = tableInfoList.begin(); it != tableInfoList.end(); it++)
		{
			if((*it)->tableID == tableID)
			{
				return (*it);
			}
		}
		return NULL;
	}

	TableInfo* FindTable(string tableName)
	{
		ListTableInfo::iterator it;

		for(it = tableInfoList.begin(); it != tableInfoList.end(); it++)
		{
			if((*it)->tableName == tableName)
			{
				return (*it);
			}
		}
		return NULL;
	}

	TableInfo* CreateTable(CreateTableData &object)
	{
		CreateIndexData *indexObject[32];
		
		KeyInfo *newKey[32];
		TableInfo *newTable;

		for(ListTableInfo::iterator it = tableInfoList.begin(); it != tableInfoList.end(); it++)
		{
			if((*it)->tableName == object.tableName)
			{
				cout<<"A table with the same name already exists."<<endl;
				return (*it);
			}
		}
		
		newTable = new TableInfo();
		//newTable->dataBlockID = NOT_FOUND;
		newTable->indexCount = 0;
		newTable->isEmpty = true;
		newTable->keyCount = 0;
		for(int i = 0; i < object.itemCount; i++)
		{
			newKey[i] = new KeyInfo();
			newKey[i]->isUnique = object.isUnique[i];
			newKey[i]->keyID = GenerateID();
			newKey[i]->keyName = object.keyName[i];
			newKey[i]->keySize = object.keySize[i];
			newKey[i]->keyType = object.keyType[i];
			newTable->keyInfoList.push_back(newKey[i]);
			newTable->keyCount++;
		}
		newTable->primaryKey = newTable->FindKey(object.primaryKeyName);
		if(newTable->primaryKey != NULL)
		{
			newTable->primaryKeyName = object.primaryKeyName;
			newTable->primaryKey->isUnique = true;
		}
		else
		{
			newTable->primaryKeyName = "???";
		}
		//newTable->rootBlockID = NOT_FOUND;
		newTable->tableID = GenerateID();
		newTable->tableName = object.tableName;
		tableInfoList.push_back(newTable);
		tableCount++;

		int i = 0;
		for(ListKeyInfo::iterator it = newTable->keyInfoList.begin(); it != newTable->keyInfoList.end(); it++)
		{
			if((*it)->isUnique == true)
			{
				IndexInfo *newIndex[32];

				indexObject[i] = new CreateIndexData();
				indexObject[i]->indexName = "???";
				indexObject[i]->indexName.assign(indexObject[i]->indexName + object.tableName);
				indexObject[i]->indexName.assign(indexObject[i]->indexName + (*it)->keyName);
				indexObject[i]->keyName = (*it)->keyName;
				indexObject[i]->tableName = newTable->tableName;

				newIndex[i] = new IndexInfo();
				newIndex[i]->dataBlockID = NOT_FOUND;
				newIndex[i]->indexID = GenerateID();
				newIndex[i]->indexKey = (IndexInfo::KeyInfo *)(*it);
				newIndex[i]->indexKeyName = indexObject[i]->keyName;
				newIndex[i]->indexName = indexObject[i]->indexName;
				newIndex[i]->indexTable = (IndexInfo::TableInfo *)newTable;
				newIndex[i]->indexTableName = indexObject[i]->tableName;
				newIndex[i]->rootBlockID = NOT_FOUND;
				newTable->indexInfoList.push_back(newIndex[i]);
				newTable->indexCount++;

				i++;
			}
		}
		cout<<"The table \""<<newTable->tableName<<"\" is successfully created."<<endl;

		return newTable;
	}

	void DropTable(int tableID)
	{
		ListTableInfo::iterator it;

		for(it = tableInfoList.begin(); it != tableInfoList.end(); it++)
		{
			if((*it)->tableID == tableID)
			{
				string tableName = (*it)->tableName;

				(*it)->Dispose();
				FreeID((*it)->tableID);
				delete (*it);
				tableInfoList.erase(it);
				tableCount--;
				cout<<"The table \""<<tableName<<"\" is successfully dropped."<<endl;
				return;
			}
		}
	}

	void DropTable(string tableName)
	{
		ListTableInfo::iterator it;

		for(it = tableInfoList.begin(); it != tableInfoList.end(); it++)
		{
			if((*it)->tableName == tableName)
			{
				(*it)->Dispose();
				FreeID((*it)->tableID);
				delete (*it);
				tableInfoList.erase(it);
				tableCount--;
				cout<<"The table \""<<tableName<<"\" is successfully dropped."<<endl;
				return;
			}
		}
		cout<<"The specified table \""<<tableName<<"\" doesn't exist in the database."<<endl;
	}

	void Dispose()
	{
		for(ListTableInfo::iterator i = tableInfoList.begin(); i != tableInfoList.end(); i++)
		{
			(*i)->Dispose();
			delete (*i);
		}
		tableInfoList.clear();
	}

	int NewBlock()
	{
		int id;

		if (emptyBlockCount == 1)
		{
			id = emptyBlockList.front();
			emptyBlockList.pop_front();
			emptyBlockList.push_back(id + 1);

			return id;
		}
		else if(emptyBlockCount <= 0)
		{
			emptyBlockCount = 1;
			emptyBlockList.clear();
			emptyBlockList.push_back(0);

			return -1;
		}
		else
		{
			emptyBlockCount--;
			id = emptyBlockList.front();
			emptyBlockList.pop_front();
			emptyBlockList.sort();

			return id;
		}
	}

	void FreeBlock(int blockId)
	{
		int id;

		if(emptyBlockCount == 1)
		{
			if(blockId < emptyBlockList.back())
			{
				if(blockId == emptyBlockList.back() - 1)
				{
					id = emptyBlockList.back();
					emptyBlockList.pop_back();
					emptyBlockList.push_back(id - 1);
				}
				else if(blockId > 0)
				{
					emptyBlockList.push_front(blockId);
					emptyBlockList.sort();
					emptyBlockCount++;
				}
			}
		}
		else if(emptyBlockCount <= 0)
		{
			emptyBlockCount = 1;
			emptyBlockList.clear();
			emptyBlockList.push_back(0);
		}
		else
		{
			if(blockId < emptyBlockList.back())
			{
				if(blockId == emptyBlockList.back() - 1)
				{
					id = emptyBlockList.back();
					emptyBlockList.pop_back();
					emptyBlockList.push_back(id - 1);
				}
				else if(blockId > 0)
				{
					ListInt::iterator it;

					for(it = emptyBlockList.begin(); it != emptyBlockList.end(); it++)
					{
						if(blockId == (*it))
							break;
					}
					if(it == emptyBlockList.end())
					{
						emptyBlockList.push_back(blockId);
						emptyBlockList.sort();
						emptyBlockCount++;
					}
				}
			}
		}
	}

	bool IsBlockUsed(int blockId)
	{
		if(blockId >= emptyBlockList.back())
		{
			return false;
		}
		else if(blockId <= 0)
		{
			return true;
		}
		else
		{
			ListInt::iterator it;

			for(it = emptyBlockList.begin(); it != emptyBlockList.end(); it++)
			{
				if(blockId == (*it))
					break;
			}
			if(it == emptyBlockList.end())
			{
				return true;//used, not in the emptyBlockList
			}
			else
			{
				return false;//not used, thus in the list.
			}
		}
	}

	int GetRootBlockId(int tableID, int indexId)
	{
		TableInfo *table;
		IndexInfo *index;

		table = FindTable(tableID);
		if(table == NULL)
			return NOT_FOUND;
		else
		{
			index = table->FindIndex(indexId);
			if(index == NULL)
			{
				return NOT_FOUND;
			}
			else
				return index->rootBlockID;
		}
	}

	int GetDataBlockId(int tableID, int indexId)
	{
		TableInfo *table;
		IndexInfo *index;

		table = FindTable(tableID);
		if(table == NULL)
			return NOT_FOUND;
		else
		{
			index = table->FindIndex(indexId);
			if(index == NULL)
			{
				return NOT_FOUND;
			}
			else
				return index->dataBlockID;
		}
	}

	void UpdateRootBlockId(int tableID, int indexId, int blockId)
	{
		TableInfo *table;
		IndexInfo *index;

		table = FindTable(tableID);
		if(table == NULL)
			return;
		else
		{
			index = table->FindIndex(indexId);
			if(index == NULL)
			{
				return;
			}
			else
				index->rootBlockID = blockId;
		}
	}

	void UpdateDataBlockId(int tableID, int indexId, int blockId)
	{
		TableInfo *table;
		IndexInfo *index;

		table = FindTable(tableID);
		if(table == NULL)
			return;
		else
		{
			index = table->FindIndex(indexId);
			if(index == NULL)
			{
				return;
			}
			else
				index->dataBlockID = blockId;
		}
	}
};

int  GenerateID();
void FreeID(int deleteID);
void ExportCatalog(CatalogInfo &cI, string fileName);
void ImportCatalog(CatalogInfo &cI, string fileName);
void ShowIndex();
void ShowIndex(string indexName);
void ShowTable();
void ShowTable(string tableName);
void SQLCreateIndex(CreateIndexData &cID);
void SQLCreateTable(CreateTableData &cTD);
void SQLDelete(DeleteData &dD);
void SQLDropIndex(string indexName);
void SQLDropTable(string tableName);
void SQLInsert(InsertData &iD);
void SQLSelect(SelectData &sD);

#endif /* _CATALOGMANAGER_H_ */
