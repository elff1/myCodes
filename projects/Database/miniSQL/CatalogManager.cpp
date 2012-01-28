#ifndef _CATALOGMANAGER_CPP_
#define _CATALOGMANAGER_CPP_

#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include "CatalogManager.h"
#include "Interpreter.h"
#include "miniSQL.h"
#include "RecordManager.h"
using namespace std;

extern CatalogInfo catalogInfo;

typedef list<int> ListID;
ListID IDList;
int IDCount;

int GenerateID()
{
	int id;

	if (IDCount == 1)
	{
		id = IDList.front();
		IDList.pop_front();
		IDList.push_back(id + 1);

		return id;
	}
	else if(IDCount <= 0)
	{
		IDCount = 1;
		IDList.clear();
		IDList.push_back(0);

		return -1;
	}
	else
	{
		IDCount--;
		id = IDList.front();
		IDList.pop_front();
		IDList.sort();

		return id;
	}
}

void FreeID(int deleteID)
{
	int id;

	if(IDCount == 1)
	{
		if(deleteID < IDList.back())
		{
			if(deleteID == IDList.back() - 1)
			{
				id = IDList.back();
				IDList.pop_back();
				IDList.push_back(id - 1);
			}
			else if(deleteID > 0)
			{
				IDList.push_front(deleteID);
				IDList.sort();
				IDCount++;
			}
		}
	}
	else if(IDCount <= 0)
	{
		IDCount = 1;
		IDList.clear();
		IDList.push_back(0);
	}
	else
	{
		if(deleteID < IDList.back())
		{
			if(deleteID == IDList.back() - 1)
			{
				id = IDList.back();
				IDList.pop_back();
				IDList.push_back(id - 1);
			}
			else if(deleteID > 0)
			{
				ListInt::iterator it;

				for(it = IDList.begin(); it != IDList.end(); it++)
				{
					if(deleteID == (*it))
						break;
				}
				if(it == IDList.end())
				{
					IDList.push_back(deleteID);
					IDList.sort();
					IDCount++;
				}
			}
		}
	}
}

void ExportCatalog(CatalogInfo &cI, string fileName)
{
	FILE *fp = fopen(fileName.data(), "w");
	if(fp == NULL)
	{
		cout<<"Cannot open export file \""<<fileName<<"\" for writing."<<endl;
		return;
	}

	fprintf(fp, "%d\n", IDCount);
	for(ListID::iterator it = IDList.begin(); it != IDList.end(); it++)
	{
		fprintf(fp, "%d\n", (*it));
	}
	fprintf(fp, "%d\n", cI.emptyBlockCount);
	for(ListInt::iterator it = cI.emptyBlockList.begin(); it != cI.emptyBlockList.end(); it++)
	{
		fprintf(fp, "%d\n", (*it));
	}
	fprintf(fp, "%d\n", cI.tableCount);
	for(ListTableInfo::iterator it = cI.tableInfoList.begin(); it != cI.tableInfoList.end(); it++)
	{
		fprintf(fp, "%d\n", (*it)->tableID);
		//fprintf(fp, "%d\n", (*it)->dataBlockID);
		//fprintf(fp, "%d\n", (*it)->rootBlockID);
		fprintf(fp, "%d\n", (*it)->keyCount);
		for(ListKeyInfo::iterator it2 = (*it)->keyInfoList.begin(); it2 != (*it)->keyInfoList.end(); it2++)
		{
			fprintf(fp, "%d\n", (*it2)->keyID);
			if((*it2)->isUnique == true)
			{
				fprintf(fp, "1\n");
			}
			else
			{
				fprintf(fp, "0\n");
			}
			fprintf(fp, "%d\n", (*it2)->keyType);
			fprintf(fp, "%d\n", (*it2)->keySize);
			fprintf(fp, "%s\n", (*it2)->keyName.data());
		}
		fprintf(fp, "%d\n", (*it)->indexCount);
		for(ListIndexInfo::iterator it3 = (*it)->indexInfoList.begin(); it3 != (*it)->indexInfoList.end(); it3++)
		{
			fprintf(fp, "%d\n", (*it3)->indexID);
			fprintf(fp, "%d\n", (*it3)->dataBlockID);
			fprintf(fp, "%d\n", (*it3)->rootBlockID);
			fprintf(fp, "%s\n", (*it3)->indexName.data());
			fprintf(fp, "%s\n", (*it3)->indexKeyName.data());
			fprintf(fp, "%s\n", (*it3)->indexTableName.data());
		}
		fprintf(fp, "%s\n", (*it)->primaryKeyName.data());
		fprintf(fp, "%s\n", (*it)->tableName.data());
	}

	fclose(fp);
}

void ImportCatalog(CatalogInfo &cI, string fileName)
{
	char buffer[256];
	FILE *fp = fopen(fileName.data(), "r");

	if(fp == NULL)
	{
		cout<<"Cannot open import file \""<<fileName<<"\" for reading."<<endl;
		return;
	}

	fscanf(fp, "%d\n", &(IDCount));
	for(int i = 0; i < IDCount; i++)
	{
		int value;

		fscanf(fp, "%d\n", &value);
		IDList.push_back(value);
	}
	IDList.sort();
	fscanf(fp, "%d\n", &(cI.emptyBlockCount));
	for(int i = 0; i < cI.emptyBlockCount; i++)
	{
		int value;

		fscanf(fp, "%d\n", &value);
		cI.emptyBlockList.push_back(value);
	}
	cI.emptyBlockList.sort();
	fscanf(fp, "%d\n", &(cI.tableCount));
	for(int i = 0; i < cI.tableCount; i++)
	{
		TableInfo *newTable;

		newTable = new TableInfo();
		fscanf(fp, "%d\n", &(newTable->tableID));
		//fscanf(fp, "%d\n", &(newTable->dataBlockID));
		//fscanf(fp, "%d\n", &(newTable->rootBlockID));
		fscanf(fp, "%d\n", &(newTable->keyCount));
		for(int i = 0; i < newTable->keyCount; i++)
		{
			int tisUnique;
			int tkeyType;
			KeyInfo *newKey;

			newKey = new KeyInfo();
			fscanf(fp, "%d\n", &(newKey->keyID));
			fscanf(fp, "%d\n", &tisUnique);
			if(tisUnique == 0)
			{
				newKey->isUnique = false;
			}
			else
			{
				newKey->isUnique = true;
			}
			fscanf(fp, "%d\n", &tkeyType);
			newKey->keyType = (DataType)tkeyType;
			fscanf(fp, "%d\n", &(newKey->keySize));
			fscanf(fp, "%s\n", buffer);
			newKey->keyName.assign(buffer);
			newTable->keyInfoList.push_back(newKey);
		}
		fscanf(fp, "%d\n", &(newTable->indexCount));
		for(int i = 0; i < newTable->indexCount; i++)
		{
			IndexInfo *newIndex;

			newIndex = new IndexInfo();
			fscanf(fp, "%d\n", &(newIndex->indexID));
			fscanf(fp, "%d\n", &(newIndex->dataBlockID));
			fscanf(fp, "%d\n", &(newIndex->rootBlockID));
			fscanf(fp, "%s\n", buffer);
			newIndex->indexName.assign(buffer);
			fscanf(fp, "%s\n", buffer);
			newIndex->indexKeyName.assign(buffer);
			ListKeyInfo::iterator it1;
			for(it1 = newTable->keyInfoList.begin(); it1 != newTable->keyInfoList.end(); it1++)
			{
				if((*it1)->keyName == newIndex->indexKeyName)
					break;
			}
			newIndex->indexKey = (IndexInfo::KeyInfo *)(*it1);
			fscanf(fp, "%s\n", buffer);
			newIndex->indexTableName.assign(buffer);
			newIndex->indexTable = (IndexInfo::TableInfo *)newTable;
			newTable->indexInfoList.push_back(newIndex);
		}
		fscanf(fp, "%s\n", buffer);
		newTable->primaryKeyName.assign(buffer);
		ListKeyInfo::iterator it1;
		for(it1 = newTable->keyInfoList.begin(); it1 != newTable->keyInfoList.end(); it1++)
		{
			if((*it1)->keyName == newTable->primaryKeyName)
				break;
		}
		newTable->primaryKey = (*it1);
		fscanf(fp, "%s\n", buffer);
		newTable->tableName.assign(buffer);
		catalogInfo.tableInfoList.push_back(newTable);
	}

	fclose(fp);
}

void ShowIndex()
{
	IndexInfo *index;
	int count;

	count = 0;
	for(ListTableInfo::iterator it = catalogInfo.tableInfoList.begin(); it != catalogInfo.tableInfoList.end(); it++)
	{
		for(ListIndexInfo::iterator it1 = (*it)->indexInfoList.begin(); it1 != (*it)->indexInfoList.end(); it1++)
		{
			string t_indexName;

			t_indexName = "???";
			t_indexName.assign(t_indexName + (*it)->tableName);
			t_indexName.assign(t_indexName + (*it1)->indexKeyName);
			
			index = (*it1);
			if(t_indexName != index->indexName)
			{
				cout<<"Index Name:"<<index->indexName<<endl;
				cout<<"Table Name:"<<index->indexTableName<<endl;
				cout<<"Key Name:"<<index->indexKeyName<<endl;
				count++;
			}
		}
	}
	if(count == 0)
	{
		cout<<"There is no index in the database.";
	}
}

void ShowIndex(string indexName)
{
	IndexInfo *index;

	for(ListTableInfo::iterator it = catalogInfo.tableInfoList.begin(); it != catalogInfo.tableInfoList.end(); it++)
	{
		for(ListIndexInfo::iterator it1 = (*it)->indexInfoList.begin(); it1 != (*it)->indexInfoList.end(); it1++)
		{
			if((*it1)->indexName == indexName)
			{
				string t_indexName;

				t_indexName = "???";
				t_indexName.assign(t_indexName + (*it)->tableName);
				t_indexName.assign(t_indexName + (*it1)->indexKeyName);

				if(t_indexName != ((*it1))->indexName)
				{
					index = (*it1);
					cout<<"Index Name:"<<index->indexName<<endl;
					cout<<"Table Name:"<<index->indexTableName<<endl;
					cout<<"Key Name:"<<index->indexKeyName<<endl;
					cout<<endl;

					return;
				}
				else
				{
					cout<<"The specified index \""<<indexName<<"\" doesn't exist."<<endl;

					return;
				}
			}
		}
	}
	cout<<"The specified index \""<<indexName<<"\" doesn't exist."<<endl;
}

void ShowTable()
{
	ListTableInfo::iterator it;

	if(catalogInfo.tableInfoList.empty() == true)
	{
		cout<<"The data base has no table in stock at the moment."<<endl;
	}
	else
	{
		for(it = catalogInfo.tableInfoList.begin(); it != catalogInfo.tableInfoList.end(); it++)
		{
			cout<<"Table ID:"<<(*it)->tableID<<endl;
			cout<<"Table Name:"<<(*it)->tableName<<endl;
			cout<<endl;
		}
	}
}

void ShowTable(string tableName)
{
	TableInfo *table;

	table = catalogInfo.FindTable(tableName);
	if(table == NULL)
	{
		cout<<"The specified table \""<<tableName<<"\" doesn't exist."<<endl;
	}
	else
	{
		cout<<"Table ID:"<<table->tableID<<endl;
		cout<<"Table Name:"<<table->tableName<<endl;
		for(ListKeyInfo::iterator it = table->keyInfoList.begin(); it != table->keyInfoList.end(); it++)
		{
			cout<<(*it)->keyName<<",";
			switch((*it)->keyType)
			{
			case TYPE_CHARS:
				{
					cout<<"char"<<",";
					cout<<(*it)->keySize - 1<<endl;
				}
				break;
			case TYPE_INT:
				{
					cout<<"int"<<",";
					cout<<(*it)->keySize<<endl;
				}
				break;
			case TYPE_FLOAT:
				{
					cout<<"float"<<",";
					cout<<(*it)->keySize<<endl;
				}
				break;
			}
		}
		cout<<"Primary Key:"<<table->primaryKeyName<<endl;
		cout<<endl;
	}
}

void SQLCreateIndex(CreateIndexData &cID)
{
	IndexInfo *newIndex;
	TableInfo *indexTable;

	cout<<"\"Create Index\" operation is triggered."<<endl;
	cout<<cID;

	indexTable = catalogInfo.FindTable(cID.tableName);
	if(indexTable == NULL)
	{
		cout<<"The specified table doesn't exist."<<endl;
		return;
	}

	newIndex = indexTable->CreateIndex(cID);
}

void SQLCreateTable(CreateTableData &cTD)
{
	TableInfo* newTable;

	cout<<"\"Create Table\" operation is triggered."<<endl;
	cout<<cTD;

	newTable = catalogInfo.CreateTable(cTD);
}

void SQLDelete(DeleteData &dD)
{
	cout<<"\"Delete\" operation is triggered."<<endl;
	cout<<dD;
	
	RcdDelete(dD);
}

void SQLDropIndex(string indexName)
{
	cout<<"\"Drop Index\" operation is triggered."<<endl;
	cout<<"Index Name:"<<indexName<<endl;

	for(ListTableInfo::iterator it = catalogInfo.tableInfoList.begin(); it != catalogInfo.tableInfoList.end(); it++)
	{
		for(ListIndexInfo::iterator it1 = (*it)->indexInfoList.begin(); it1 != (*it)->indexInfoList.end(); it1++)
		{
			if((*it1)->indexName == indexName)
			{
				string t_indexName;

				t_indexName = "???";
				t_indexName.assign(t_indexName + (*it)->tableName);
				t_indexName.assign(t_indexName + (*it1)->indexKeyName);

				if(t_indexName == indexName)
				{
					cout<<"The specified index doesn't exist in the database."<<endl;
					return;
				}
				else
				{
					(*it1)->indexName = "???";
					(*it1)->indexName.assign((*it1)->indexName + (*it)->tableName);
					(*it1)->indexName.assign((*it1)->indexName + (*it1)->indexKeyName);
					cout<<"The index \""<<indexName<<"\" has been dropped."<<endl;
					return;
				}
			}
		}
	}
	cout<<"The specified index doesn't exist in the database."<<endl;
}

void SQLDropTable(string tableName)
{
	cout<<"\"Drop Table\" operation is triggered."<<endl;
	cout<<"Table Name:"<<tableName<<endl;

	catalogInfo.DropTable(tableName);
}

void SQLInsert(InsertData &iD)
{
	//cout<<"\"Insert\" operation is triggered."<<endl;
	//cout<<iD;
	
	RcdInsert(iD);
}

void SQLSelect(SelectData &sD)
{
	cout<<"\"Select\" operation is triggered."<<endl;
	cout<<sD;
	
	RcdSelect(sD);
}

#endif /* _CATALOGMANAGER_CPP_ */
