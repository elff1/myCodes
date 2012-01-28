#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <fstream>
#include <string>
#include "miniSQL.h"

using namespace std;

class Condition//needed by SELECT and DELETE operations.
{
public:
	ComparisonType comptype;//the type of comparison
	string keyName;         //the name of key
	string dataValue;       //the value section
	unsigned int dataType;  //the type of the value
};

class CreateIndexData
{
public:
	string indexName;//the name of the index
	string keyName;  //the key of the index
	string tableName;//the table for which the index is to be created
	friend ostream& operator << (ostream &os, CreateIndexData &cID);
};

class CreateTableData
{
public:
	string tableName;              //the table to be created
	bool isUnique[MAX_ITEM_NUM];   //whether each key is unique
	string keyName[MAX_ITEM_NUM];  //the name of each key
	string typeName[MAX_ITEM_NUM]; //the type name of each key
	DataType keyType[MAX_ITEM_NUM];//the type of each key
	size_t keySize[MAX_ITEM_NUM];  //the number of bytes required for each key
	string primaryKeyName;         //the name of primary key
	int itemCount;                 //the number of keys

	friend ostream& operator << (ostream &os, CreateTableData &cTD);
};

class DeleteData
{
public:
	string tableName;                 //from table
	Condition condition[MAX_ITEM_NUM];//the conditions to be judged.
	int itemCount;                    //the number of conditions

	friend ostream& operator << (ostream &os, DeleteData &dD);
	//Since there's only AND operation between these conditions, no more data is needed here.
};

//class DropIndexData is not needed.
//only one string is enough, thus no need to define a class here.
//string dropIndexName;

//class DropTableData is not needed.
//only one string is enough, thus no need to define a class here.
//string dropTableName;

//class ExecFileData is not needed.
//only one string is enough, thus no need to define a class here.
//string sQLFileName;

class InsertData
{
public:
	string tableName;               //insert into this table
	string dataValue[MAX_ITEM_NUM]; //the value of each key
	unsigned int dataType[MAX_ITEM_NUM];//the type of each key
	int itemCount;                  //the number of keys

	friend ostream& operator << (ostream &cout, InsertData &iD);
	//size_t keySize[MAX_ITEM_NUM];//the number of bytes required for each key
	//I don't think it's needed here, but if you do, you can add it to the class
};

class SelectData
{
public:
	string tableName;                 //from table
	Condition condition[MAX_ITEM_NUM];//the conditions to be judged.
	int itemCount;                    //the number of conditions

	friend ostream& operator << (ostream &cout, SelectData &sD);
	//Since there's only AND operation between these conditions, no more data is needed here.
};

bool isblank(const char ch);
bool GetLine(char str[],const int maxlen, const char stopChar);
bool GetLineF(char str[],const int maxlen, const char stopChar, ifstream &ifs);
unsigned int GetType(string dataValue);
int  CutString(const char instr[], char out[][MAX_ITEM_LENGTH], const int maxarg);
void FillLine(char str[], const char fillCharLeft, const char fillCharRight, const int lineWidth);
void Standardize(char str[], const char stopChar);
void WelcomeInfo();
bool ExecSQL(string strs[], int argc, ifstream &SQLFile);

#endif /* _INTERPRETER_H_ */
