#ifndef _INTERPRETER_CPP_
#define _INTERPRETER_CPP_

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include "CatalogManager.h"
#include "Interpreter.h"
#include "miniSQL.h"

using namespace std;

ostream& operator << (ostream &cout, CreateIndexData &cID)
{
	cout<<"Index Name:"<<cID.indexName<<endl;
	cout<<"Table Name:"<<cID.tableName<<endl;
	cout<<"Key Name:"<<cID.keyName<<endl;

	return cout;
}

ostream& operator << (ostream &cout, CreateTableData &cTD)
{
	cout<<"Table Name:"<<cTD.tableName<<endl;
	cout<<"Keys:"<<endl;
	for(int i = 0; i < cTD.itemCount; i++)
	{
		cout<<"Keys["<<i<<"]:";
		if(cTD.isUnique[i] == true)
			cout<<"UNIQUE";
		cout<<endl;
		cout<<"    Key Name:"<<cTD.keyName[i]<<endl;
		cout<<"    Type Name:"<<cTD.typeName[i]<<endl;
		cout<<"    Key Size:"<<cTD.keySize[i]<<endl;
	}
	cout<<"Primary Key:"<<cTD.primaryKeyName<<endl;

	return cout;
}

ostream& operator << (ostream &os, DeleteData &dD)
{
	cout<<"Table Name:"<<dD.tableName<<endl;
	if(dD.itemCount > 0)
	{
		cout<<"Conditions:"<<endl;
		for(int i = 0; i < dD.itemCount; i++)
		{
			cout<<dD.condition[i].keyName;
			switch(dD.condition[i].comptype)
			{
			case LESS_THAN:
				{
					cout<<"<";
				}
				break;
			case LESS_EQUAL:
				{
					cout<<"<=";
				}
				break;
			case EQUAL:
				{
					cout<<"=";
				}
				break;
			case GREATER_EQUAL:
				{
					cout<<">=";
				}
				break;
			case GREATER_THAN:
				{
					cout<<">";
				}
				break;
			case NOT_EQUAL:
				{
					cout<<"!=";
				}
				break;
			}
			cout<<dD.condition[i].dataValue<<endl;
		}
	}

	return cout;
}

ostream& operator << (ostream &cout, InsertData &iD)
{
	cout<<"Table Name:"<<iD.tableName<<endl;
	cout<<"Values:"<<endl;
	for(int i = 0; i < iD.itemCount; i++)
	{
		cout<<iD.dataValue[i]<<":";
		switch(iD.dataType[i])
		{
		case TYPE_CHARS:
			cout<<"chars";
			break;
		case TYPE_FLOAT:
			cout<<"float";
			break;
		case TYPE_INT:
			cout<<"int";
			break;
		default:
			cout<<"error";
		}
		cout<<endl;
	}

	return cout;
}

ostream& operator << (ostream &cout, SelectData &sD)
{
	cout<<"Table Name:"<<sD.tableName<<endl;
	if(sD.itemCount > 0)
	{
		cout<<"Conditions:"<<endl;
		for(int i = 0; i < sD.itemCount; i++)
		{
			cout<<sD.condition[i].keyName;
			switch(sD.condition[i].comptype)
			{
			case LESS_THAN:
				{
					cout<<"<";
				}
				break;
			case LESS_EQUAL:
				{
					cout<<"<=";
				}
				break;
			case EQUAL:
				{
					cout<<"=";
				}
				break;
			case GREATER_EQUAL:
				{
					cout<<">=";
				}
				break;
			case GREATER_THAN:
				{
					cout<<">";
				}
				break;
			case NOT_EQUAL:
				{
					cout<<"!=";
				}
				break;
			}
			cout<<sD.condition[i].dataValue<<endl;
		}
	}

	return cout;
}

bool isblank(const char ch)
{
	if(ch == ' ' || ch == '\t')
		return true;
	else
		return false;
}

bool GetLine(char str[],const int maxlen, const char stopChar)
{
	int i;
	bool singleQuote;
	bool doubleQuote;

	gets_s(str, MAX_LINE_LENGTH);

	i = 0;
	singleQuote = false;
	doubleQuote  =false;
	while(1)
	{
		if(str[i] == '\0')
		{
			return true;
		}
		else if(str[i] == '\'')
		{
			singleQuote = !singleQuote;
			i++;
		}
		else if(str[i] == '\"')
		{
			doubleQuote = !doubleQuote;
			i++;
		}
		else if(str[i] == stopChar)
		{
			if(singleQuote == false && doubleQuote == false)
			{
				str[i + 1] = '\0';
				return false;
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
}

bool GetLineF(char str[],const int maxlen, const char stopChar, ifstream &ifs)
{
	int i;
	bool singleQuote;
	bool doubleQuote;

	if(ifs.is_open() == false)
		return false;

	ifs.getline(str, MAX_CHR_BUFFER_LEN);
	if(ifs.peek() == EOF)
	{
		return false;
	}

	i = 0;
	singleQuote = false;
	doubleQuote  =false;
	while(1)
	{
		if(str[i] == '\0')
		{
			return true;
		}
		else if(str[i] == '\'')
		{
			singleQuote = !singleQuote;
			i++;
		}
		else if(str[i] == '\"')
		{
			doubleQuote = !doubleQuote;
			i++;
		}
		else if(str[i] == stopChar)
		{
			if(singleQuote == false && doubleQuote == false)
			{
				str[i + 1] = '\0';
				return false;
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
}

unsigned int GetType(string dataValue)
{
	char buffer[MAX_CHR_BUFFER_LEN];
	unsigned int result = 0;
	int i;
	int dotCount;

	strcpy(buffer, dataValue.data());

	if(buffer[0] == '\'')
	{
		if(buffer[strlen(buffer) - 1] == '\'')
		{
			result = BIT_CHARS;
			return result;
		}
		else
		{
			result = 0;
			return result;
		}
	}

	if(buffer[0] == '\"')
	{
		if(buffer[strlen(buffer) - 1] == '\"')
		{
			result = BIT_CHARS;
			return result;
		}
		else
		{
			result = 0;
			return result;
		}
	}

	if(buffer[0] == '+' || buffer[0] == '-')
	{
		string newString;
		

		return GetType(newString.assign(buffer + 1));
	}

	for(i = 0; i < strlen(buffer); i++)
	{
		if((buffer[i] > '9' || buffer[i] < '0') && buffer[i] != '.')
		{
			result = 0;
			return result;
		}
	}

	dotCount = 0;
	for(i = 0; i < strlen(buffer); i++)
	{
		if(buffer[i] == '.')
		{
			dotCount++;
		}
	}
	if(dotCount == 0)
	{
		result = BIT_FLOAT | BIT_INT;
		return result;
	}
	else if(dotCount == 1)
	{
		result = BIT_FLOAT;
		return result;
	}
	else
	{
		result = 0;
		return result;
	}
}

int CutString(const char instr[], char out[][MAX_ITEM_LENGTH], const int maxarg)
{
	int i, j;
	int n;
	bool copy;
	bool singleQuote;
	bool doubleQuote;

	i = 0;
	j = 0;
	n = 0;
	copy = false;
	singleQuote = false;
	doubleQuote = false;
	while(1)
	{
		if(instr[i + j] == '\0')
		{
			out[n][j] = 0;
			n++;
			break;
		}
		else if(instr[i + j] == '\'')
		{
			singleQuote = !singleQuote;
		}
		else if(instr[i + j] == '\"')
		{
			doubleQuote = !doubleQuote;
		}

		if(copy == true)
		{
			if(!isblank(instr[i + j]))
			{
				out[n][j] = instr[i + j];
				j++;
			}
			else
			{
				if(singleQuote == false && doubleQuote == false)
				{
					out[n][j] = '\0';
					n++;
					if(n == maxarg)
						break;
					i = i + j;
					j = 0;
					copy = false;
				}
				else
				{
					out[n][j] = instr[i + j];
					j++;
				}
			}
		}
		else if(!isblank(instr[i + j]))
		{
			copy = true;
			out[n][j] = instr[i + j];
			j++;
		}
		else
			i++;
	}

	return n;
}

void FillLine(char str[], const char fillCharLeft, const char fillCharRight, const int lineWidth)
{
	char buffer[MAX_CHR_BUFFER_LEN];
	int i, j;
	int len = strlen(str);
	
	if(len >= lineWidth)
		return;

	j = 0;
	for(i = 0; i < (lineWidth - len - 1) / 2; i++)
	{
		buffer[j] = fillCharLeft;
		j++;
	}
	buffer[j] = 0;
	strcat(buffer, str);
	j = strlen(buffer);
	for(int i = 0; i < (lineWidth - len + 1) / 2; i++)
	{
		buffer[j] = fillCharRight;
		j++;
	}
	buffer[j] = 0;
	strcpy(str, buffer);
}

void Standardize(char str[], const char stopChar)
{
	int i, j;
	bool blank;
	bool stop;
	char buffer[MAX_CHR_BUFFER_LEN];
	bool singleQuote;
	bool doubleQuote;

	i = 0;
	j = 0;
	singleQuote = false;
	doubleQuote = false;
	while(1)
	{
		switch(str[i])
		{
		case '*':
		case ',':
		case '(':
		case ')':
		case ';':
			{
				if(singleQuote == false == doubleQuote == false)
				{
					buffer[j] = ' ';
					j++;
					buffer[j] = str[i];
					j++;
					buffer[j] = ' ';
					j++;
				}
				else
				{
					buffer[j] = str[i];
					j++;
				}
			}
			break;
		case '=':
		case '<':
			{
				if(singleQuote == false && doubleQuote == false)
				{
					if(str[i + 1] == '=' || str[i + 1] == '>')
					{
						buffer[j] = ' ';
						j++;
						buffer[j] = str[i];
						i++;
						j++;
						buffer[j] = str[i];
						j++;
						buffer[j] = ' ';
						j++;
					}
					else
					{
						buffer[j] = ' ';
						j++;
						buffer[j] = str[i];
						j++;
						buffer[j] = ' ';
						j++;
					}
				}
				else
				{
					buffer[j] = str[i];
					j++;
				}
			}
			break;
		case '>':
		case '!':
			{
				if(singleQuote == false && doubleQuote == false)
				{
					if(str[i + 1] == '=')
					{
						buffer[j] = ' ';
						j++;
						buffer[j] = str[i];
						i++;
						j++;
						buffer[j] = str[i];
						j++;
						buffer[j] = ' ';
						j++;
					}
					else
					{
						buffer[j] = ' ';
						j++;
						buffer[j] = str[i];
						j++;
						buffer[j] = ' ';
						j++;
					}
				}
				else
				{
					buffer[j] = str[i];
					j++;
				}
			}
			break;
		case '\'':
			{
				buffer[j] = str[i];
				j++;
				singleQuote = !singleQuote;
			}
			break;
		case '\"':
			{
				buffer[j] = str[i];
				j++;
				doubleQuote = !doubleQuote;
			}
			break;
		default:
			{
				buffer[j] = str[i];
				j++;
			}
		}
		i++;
		if(str[i] == '\0')
		{
			strcpy(str, buffer);
			break;
		}
	}

	i = 0;
	singleQuote = false;
	doubleQuote = false;
	while(1)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 'a' - 'A';
			i++;
		}
		else if(str[i] == '\'')
		{
			singleQuote = !singleQuote;
			i++;
		}
		else if(str[i] == '\"')
		{
			doubleQuote = !doubleQuote;
			i++;
		}
		else if(str[i] == stopChar)
		{
			if(singleQuote == false && doubleQuote == false)
			{
				str[i + 1] = '\0';
				break;
			}
			else
			{
				i++;
			}
		}
		else if(str[i] == '\0')
			break;
		else
			i++;
	}

	i = 0;
	j = 0;
	blank = false;
	while(1)
	{
		if(isblank(str[i]) == true)
		{
			if(blank == true)
			{
				i++;
			}
			else
			{
				blank = true;
				buffer[j] = str[i];
				i++;
				j++;
			}
		}
		else if(str[i] == '\0')
		{
			buffer[j] = str[i];
			i++;
			j++;
			break;
		}
		else
		{
			if(blank == true)
				blank = false;
			buffer[j] = str[i];
			i++;
			j++;
		}
	}

	stop = false;
	i = strlen(buffer);
	while(i >= 0)
	{
		if(stop == true)
		{
			if(isblank(buffer[i]) == true)
			{
				i--;
			}
			else
			{
				buffer[i + 1] = stopChar;
				buffer[i + 2] = '\0';
				break;
			}
		}
		else
		{
			if(buffer[i] == stopChar)
			{
				stop = true;
			}
			i--;
		}
	}

	strcpy(str, buffer);
	str[strlen(str) - 1] = 0;
}

void WelcomeInfo()
{
	char line1[MAX_LINE_LENGTH] = "MiniSQL Data Base Management System v1.16.2";
	char line2[MAX_LINE_LENGTH] = "2011.11.16";

	FillLine(line1, '-', '-', 80);
	FillLine(line2, '>', '<', 80);
	puts(line1);
	puts(line2);
}

bool ExecSQL(string strs[], int argc, ifstream &SQLFile)
{
	int i;
	char buffer[MAX_CHR_BUFFER_LEN];
	ParseState parseState;
	string helpCommandInfo[12] = {
		"help    ", "Display this help message.",
		"clear   ", "Clear the screen.",
		"execfile", "Execute an SQL script file.",
		"show    ", "Show the information about the tables in the database.",
		"exit    ", "Exit the program.",
		"quit    ", "Exit the program."
	};
	string SQLCommandInfo[10] = {
		"create  ", "Create a table or an index.",
		"delete  ", "Delete records from a table.",
		"drop    ", "Drop a table or an index",
		"insert  ", "Insert records into a table.",
		"select  ", "Search records from the "
	};

	//Objects of the data required for the query are declared here.
	CreateIndexData createIndexData;
	CreateTableData createTableData;
	DeleteData deleteData;
	string dropIndexData;
	string dropTableData;
	InsertData insertData;
	SelectData selectData;
	string indexName;
	string tableName;

	//Necessary initializations
	createTableData.itemCount = 0;
	deleteData.itemCount = 0;
	insertData.itemCount = 0;
	selectData.itemCount = 0;

	i = 0;
	parseState = INITIAL;
	while(1)
	{
		switch (parseState)
		{
		case INITIAL:
			if(i == argc)
			{
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return true;
			}
			else if(strs[i] == "clear")
			{
				parseState = CLEAR;
			}
			else if(strs[i] == "create")
			{
				parseState = CREATE;
			}
			else if(strs[i] == "delete")
			{
				parseState = DELETE;
			}
			else if(strs[i] == "drop")
			{
				parseState = DROP;
			}
			else if(strs[i] == "execfile")
			{
				parseState = EXECFILE;
			}
			else if(strs[i] == "exit" || strs[i] == "quit")
			{
				cout<<"Bye:)"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return true;
			}
			else if(strs[i] == "help")
			{
				parseState = HELP;
			}
			else if(strs[i] == "insert")
			{
				parseState = INSERT;
			}
			else if(strs[i] == "select")
			{
				parseState = SELECT;
			}
			else if(strs[i] == "show")
			{
				parseState = SHOW;
			}
			else
			{
				parseState = ERROR_UNKNOWN_COMMAND;
			}
			break;
		case CLEAR:
			{
				system("cls");
				WelcomeInfo();
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case CREATE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "index")
			{
				parseState = CREATE_INDEX;
			}
			else if (strs[i] == "table")
			{
				parseState = CREATE_TABLE;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				createTableData.tableName.assign(strs[i]);
				parseState = CREATE_TABLE_TABLENAME;
			}
			break;
		case CREATE_TABLE_TABLENAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "(")
			{
				parseState = CREATE_TABLE_LB;
			}
			else
			{
				parseState = ERROR_KEYLIST_REQUIRED;
			}
			break;
		case CREATE_TABLE_LB:
			if (i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				createTableData.keyName[createTableData.itemCount].assign(strs[i]);
				parseState = CREATE_TABLE_KEYNAME;
			}
			break;
		case CREATE_TABLE_KEYNAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "char")
			{
				createTableData.typeName[createTableData.itemCount].assign(strs[i]);
				createTableData.keyType[createTableData.itemCount] = TYPE_CHARS;
				parseState = CREATE_TABLE_CHAR;
			}
			else if(strs[i] == "float")
			{
				createTableData.keySize[createTableData.itemCount] = sizeof(float);
				createTableData.typeName[createTableData.itemCount].assign(strs[i]);
				createTableData.keyType[createTableData.itemCount] = TYPE_FLOAT;
				parseState = CREATE_TABLE_KEYTYPE;
			}
			else if(strs[i] == "int")
			{
				createTableData.keySize[createTableData.itemCount] = sizeof(int);
				createTableData.typeName[createTableData.itemCount].assign(strs[i]);
				createTableData.keyType[createTableData.itemCount] = TYPE_INT;
				parseState = CREATE_TABLE_KEYTYPE;
			}
			else
			{
				parseState = ERROR_UNKNOWN_DATATYPE;
			}
			break;
		case CREATE_TABLE_KEYTYPE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if (strs[i] == "unique")
			{
				createTableData.isUnique[createTableData.itemCount] = true;
				parseState = CREATE_TABLE_UNIQUE;
			}
			else if(strs[i] == ",")
			{
				createTableData.isUnique[createTableData.itemCount] = false;
				createTableData.itemCount++;
				parseState = CREATE_TABLE_KEYNAME_COMMA;
			}
			else if(strs[i] == ")")
			{
				parseState = ERROR_PRIMARY_KEY_REQUIRED;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_UNIQUE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == ",")
			{
				createTableData.itemCount++;
				parseState = CREATE_TABLE_KEYNAME_COMMA;
			}
			else if(strs[i] == ")")
			{
				parseState = ERROR_PRIMARY_KEY_REQUIRED;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_KEYNAME_COMMA:
			if (i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "primary")
			{
				parseState = CREATE_TABLE_PRIMARY;
			}
			else
			{
				int j;

				if(createTableData.itemCount > 0)
				{
					for(j = 0; j < createTableData.itemCount; j++)
					{
						if(strs[i] == createTableData.keyName[j])
						{
							break;
						}
					}
				}
				if(j == createTableData.itemCount)
				{
					if(createTableData.itemCount == MAX_ITEM_NUM)
					{
						parseState = ERROR_TOO_MANY_KEYS;
					}
					else
					{
						createTableData.keyName[createTableData.itemCount].assign(strs[i]);
						parseState = CREATE_TABLE_KEYNAME;
					}
				}
				else
				{
					parseState = ERROR_KEY_ALREADY_EXISTS;
				}
			}
			break;
		case CREATE_TABLE_CHAR:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "(")
			{
				parseState = CREATE_TABLE_CHAR_LB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_CHAR_LB:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				size_t t_size;

				t_size = (size_t)atoi(strs[i].data());
				if(t_size > 255 || t_size <= 0)
				{
					parseState = ERROR_INVALID_STRING_SIZE;
				}
				else
				{
					t_size++;
					createTableData.keySize[createTableData.itemCount] = t_size;
					parseState = CREATE_TABLE_CHAR_SIZE;
				}
			}
			break;
		case CREATE_TABLE_CHAR_SIZE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == ")")
			{
				parseState = CREATE_TABLE_CHAR_RB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_CHAR_RB:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "unique")
			{
				createTableData.isUnique[createTableData.itemCount] = true;
				parseState = CREATE_TABLE_UNIQUE;
			}
			else if(strs[i] == ",")
			{
				createTableData.isUnique[createTableData.itemCount] = false;
				createTableData.itemCount++;
				parseState = CREATE_TABLE_KEYNAME_COMMA;
			}
			else if(strs[i] == ")")
			{
				parseState = ERROR_PRIMARY_KEY_REQUIRED;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_PRIMARY:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if (strs[i] == "key")
			{
				parseState = CREATE_TABLE_PRIMARY_KEY;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_PRIMARY_KEY:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "(")
			{
				parseState = CREATE_TABLE_PRIMARY_KEY_LB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_PRIMARY_KEY_LB:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				bool found = false;

				for(int j = 0; j < createTableData.itemCount; j++)
				{
					if(strs[i] == createTableData.keyName[j])
					{
						found = true;
						break;
					}
				}
				if(found == true)
				{
					createTableData.primaryKeyName.assign(strs[i]);
					parseState = CREATE_TABLE_PRIMARY_KEY_KEYNAME;
				}
				else
				{
					parseState = ERROR_PRIMARY_KEY_NOT_FOUND;
				}
			}
			break;
		case CREATE_TABLE_PRIMARY_KEY_KEYNAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if (strs[i] == ")")
			{
				parseState = CREATE_TABLE_PRIMARY_KEY_RB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_PRIMARY_KEY_RB:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == ")")
			{
				parseState = CREATE_TABLE_RB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_TABLE_RB:
			if(i == argc)
			{
				SQLCreateTable(createTableData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_INDEX:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				createIndexData.indexName.assign(strs[i]);
				parseState = CREATE_INDEX_INDEXNAME;
			}
			break;
		case CREATE_INDEX_INDEXNAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "on")
			{
				parseState = CREATE_INDEX_ON;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_INDEX_ON:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				createIndexData.tableName.assign(strs[i]);
				parseState = CREATE_INDEX_TABLENAME;
			}
			break;
		case CREATE_INDEX_TABLENAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "(")
			{
				parseState = CREATE_INDEX_LB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_INDEX_LB:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				createIndexData.keyName.assign(strs[i]);
				parseState = CREATE_INDEX_KEYNAME;
			}
			break;
		case CREATE_INDEX_KEYNAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == ")")
			{
				parseState = CREATE_INDEX_RB;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case CREATE_INDEX_RB:
			if(i == argc)
			{
				SQLCreateIndex(createIndexData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DELETE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if (strs[i] == "from")
			{
				parseState = DELETE_FROM;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DELETE_FROM:
			if(i == argc)
			{
				parseState = ERROR_TABLENAME_REQUIRED;
			}
			else
			{
				deleteData.tableName.assign(strs[i]);
				parseState = DELETE_FROM_TABLENAME;
			}
			break;
		case DELETE_FROM_TABLENAME:
			if(i == argc)
			{
				SQLDelete(deleteData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else if(strs[i] == "where")
			{
				parseState = DELETE_FROM_WHERE;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DELETE_FROM_WHERE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				deleteData.condition[deleteData.itemCount].keyName.assign(strs[i]);
				parseState = DELETE_FROM_KEYNAME;
			}
			break;
		case DELETE_FROM_KEYNAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "<")
			{
				deleteData.condition[deleteData.itemCount].comptype = LESS_THAN;
				parseState = DELETE_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == "<=")
			{
				deleteData.condition[deleteData.itemCount].comptype = LESS_EQUAL;
				parseState = DELETE_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == "=" || strs[i] == "==")
			{
				deleteData.condition[deleteData.itemCount].comptype = EQUAL;
				parseState = DELETE_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == ">=")
			{
				deleteData.condition[deleteData.itemCount].comptype = GREATER_EQUAL;
				parseState = DELETE_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == ">")
			{
				deleteData.condition[deleteData.itemCount].comptype = GREATER_THAN;
				parseState = DELETE_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == "!=" || strs[i] == "<>")
			{
				deleteData.condition[deleteData.itemCount].comptype = NOT_EQUAL;
				parseState = DELETE_FROM_COMPARISON_TYPE;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DELETE_FROM_COMPARISON_TYPE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				unsigned int result;

				deleteData.condition[deleteData.itemCount].dataValue.assign(strs[i]);
				result = GetType(deleteData.condition[deleteData.itemCount].dataValue);
				deleteData.condition[deleteData.itemCount].dataType = result;
				if((result & BIT_CHARS) != 0)
				{
					strcpy(buffer, deleteData.condition[deleteData.itemCount].dataValue.data());
					buffer[strlen(buffer) - 1] = 0;
					strcpy(buffer, buffer + 1);
					deleteData.condition[deleteData.itemCount].dataValue.assign(buffer);
				}
				deleteData.itemCount++;
				parseState = DELETE_FROM_KEYVALUE;
			}
			break;
		case DELETE_FROM_KEYVALUE:
			if(i == argc)
			{
				SQLDelete(deleteData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else if(strs[i] == "and")
			{
				parseState = DELETE_FROM_AND;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DELETE_FROM_AND:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				deleteData.condition[deleteData.itemCount].keyName.assign(strs[i]);
				parseState = DELETE_FROM_KEYNAME;
			}
			break;
		case DROP:
			if (i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "table")
			{
				parseState = DROP_TABLE;
			}
			else if(strs[i] == "index")
			{
				parseState = DROP_INDEX;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DROP_TABLE:
			if(i == argc)
			{
				parseState = ERROR_TABLENAME_REQUIRED;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				dropTableData.assign(strs[i]);
				parseState = DROP_TABLE_TABLENAME;
			}
			break;
		case DROP_TABLE_TABLENAME:
			if(i == argc)
			{
				SQLDropTable(dropTableData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case DROP_INDEX:
			if(i == argc)
			{
				parseState = ERROR_INDEXNAME_REQUIRED;
			}
			else
			{
				dropIndexData.assign(strs[i]);
				parseState = DROP_INDEX_INDEXNAME;
			}
			break;
		case DROP_INDEX_INDEXNAME:
			if(i == argc)
			{
				SQLDropIndex(dropIndexData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case ERROR_FILENAME_REQUIRED:
			{
				cout<<"ERROR:The name of the SQL script file is required."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_INDEXNAME_NOT_FOUND:
			{
				cout<<"ERROR:The specified index doesn't exist in the database."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_INDEXNAME_REQUIRED:
			{
				cout<<"The name of the index is required."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_INVALID_STRING_SIZE:
			{
				cout<<"ERROR:The size of the char is invalid."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_INVALID_VALUE:
			{
				cout<<"ERROR:The input value is invalid."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_KEY_ALREADY_EXISTS:
			{
				cout<<"Multiple keys with the same name are not allowed."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_KEYLIST_REQUIRED:
			{
				cout<<"A list of keys is required to create the table."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_KEYNAME_NOT_FOUND:
			{
				cout<<"ERROR:The specified key doesn't exist in the table."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_NOT_ENOUGH_PARAMETER:
			{
				cout<<"ERROR:More parameters are required for this command."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_PRIMARY_KEY_NOT_FOUND:
			{
				//cout<<"ERROR:The specified primary key doesn't exist in the table."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				throw ErMorePara();
				return false;
			}
			break;
		case ERROR_PRIMARY_KEY_REQUIRED:
			{
				cout<<"ERROR:The primary key must be specified for the table."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_SYNTAX:
			{
				cout<<"ERROR:There are some problems with the syntax of your command."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_TABLENAME_NOT_FOUND:
			{
				cout<<"ERROR:The specified table doesn't exist in the database."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_TABLENAME_REQUIRED:
			{
				cout<<"The name of the table is required."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_TOO_MANY_CONDITIONS:
			{
				cout<<"ERROR:At most "<<MAX_ITEM_NUM<<" conditions are allowed in one query."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_TOO_MANY_KEYS:
			{
				cout<<"ERROR:At most "<<MAX_ITEM_NUM<<" keys are allowed in one table."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_UNKNOWN_COMMAND:
			{
				cout<<"ERROR:Unknown command, please type in \"help\" to view the usage."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case ERROR_UNKNOWN_DATATYPE:
			{
				cout<<"ERROR:Unknown key type --> "<<strs[i - 1]<<" ."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case EXECFILE:
			if(i == argc)
			{
				parseState = ERROR_FILENAME_REQUIRED;
			}
			else
			{
				SQLFile.close();
				SQLFile.open(strs[i].data(), ios::beg);
				if(SQLFile.is_open() == false)
				{
					cout<<"ERROR:File doesn't exist."<<endl;
					return false;
				}
				return false;
			}
			break;
		case HELP:
			if(i == argc)
			{
				cout<<"Here are the commands available for use:"<<endl;
				for(int j = 0; j < 8; j+=2)
				{
					cout<<helpCommandInfo[j]<<":"<<helpCommandInfo[j + 1]<<endl;
				}
				cout<<endl;

				cout<<"The following are SQL command:"<<endl;
				for(int j = 0; j < 10; j+=2)
				{
					cout<<SQLCommandInfo[j]<<":"<<SQLCommandInfo[j + 1]<<endl;
				}
				cout<<"Please type in \"help <SQL command>\" to see more."<< endl;

				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else if(strs[i] == "create")
			{
				parseState = HELP_CREATE;
			}
			else if(strs[i] == "delete")
			{
				parseState = HELP_DELETE;
			}
			else if(strs[i] == "drop")
			{
				parseState = HELP_DROP;
			}
			else if(strs[i] == "execfile")
			{
				parseState = HELP_EXECFILE;
			}
			else if(strs[i] == "insert")
			{
				parseState = HELP_INSERT;
			}
			else if(strs[i] == "select")
			{
				parseState = HELP_SELECT;
			}
			else if(strs[i] == "show")
			{
				parseState = HELP_SHOW;
			}
			else
			{
				cout<<"Here are the commands available for use:"<<endl;
				for(int j = 0; j < 8; j+=2)
				{
					cout<<SQLCommandInfo[j]<<":"<<SQLCommandInfo[j + 1]<<endl;
				}

				cout<<"The following are SQL command:"<<endl;
				for(int j = 0; j < 10; j+=2)
				{
					cout<<SQLCommandInfo[j]<<":"<<SQLCommandInfo[j + 1]<<endl;
				}
				cout<<"Please type in \"help <SQL command>\" to see more."<< endl;

				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_CREATE:
			{
				cout<<"USAGE:"<<endl;
				cout<<"create index <index name> on <table name> (<key name>)"<<endl;
				cout<<"create table <table name> (<key name, key type>, primary key (<primary key name>) );"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_DELETE:
			{
				cout<<"USAGE:"<<endl;
				cout<<"delete from <table name> [where <key name> <operator> <value> ...];"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_DROP:
			{
				cout<<"USAGE:"<<endl;
				cout<<"drop index <index name>"<<endl;
				cout<<"drop table <table name>"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_EXECFILE:
			{
				cout<<"USAGE:"<<endl;
				cout<<"execfile <SQL file name>;"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_INSERT:
			{
				cout<<"USAGE:"<<endl;
				cout<<"insert into <table name> values(<value1>, <value2>, ...);"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_SELECT:
			{
				cout<<"USAGE:"<<endl;
				cout<<"select from <table name> [where <key name> <operator> <value> ...];"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case HELP_SHOW:
			{
				cout<<"USAGE:"<<endl;
				cout<<"show table <table name>;"<<endl;
				cout<<"show tables;"<<endl;
				cout<<"show index <index name>;"<<endl;
				cout<<"show indices;"<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			break;
		case INSERT:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "into")
			{
				parseState = INSERT_INTO;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case INSERT_INTO:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				insertData.tableName.assign(strs[i]);
				parseState = INSERT_INTO_TABLENAME;
			}
			break;
		case INSERT_INTO_TABLENAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if (strs[i] == "values")
			{
				parseState = INSERT_INTO_VALUES;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case INSERT_INTO_VALUES:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "(")
			{
				parseState = INSERT_INTO_LB;
			}
			break;
		case INSERT_INTO_LB:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				unsigned result;

				insertData.dataValue[insertData.itemCount].assign(strs[i]);
				result = GetType(insertData.dataValue[insertData.itemCount]);
				insertData.dataType[insertData.itemCount] = result;
				if((result & BIT_CHARS) != 0)
				{
					strcpy(buffer, insertData.dataValue[insertData.itemCount].data());
					buffer[strlen(buffer) - 1] = 0;
					strcpy(buffer, buffer + 1);
					insertData.dataValue[insertData.itemCount].assign(buffer);
				}
				insertData.itemCount++;
				parseState = INSERT_INTO_KEYVALUE;
			}
			break;
		case INSERT_INTO_KEYVALUE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == ",")
			{
				parseState = INSERT_INTO_COMMA;
			}
			else if(strs[i] == ")")
			{
				parseState = INSERT_INTO_RB;
			}
			break;
		case INSERT_INTO_COMMA:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				unsigned result;

				insertData.dataValue[insertData.itemCount].assign(strs[i]);
				result = GetType(insertData.dataValue[insertData.itemCount]);
				insertData.dataType[insertData.itemCount] = result;
				if((result & BIT_CHARS) != 0)
				{
					strcpy(buffer, insertData.dataValue[insertData.itemCount].data());
					buffer[strlen(buffer) - 1] = 0;
					strcpy(buffer, buffer + 1);
					insertData.dataValue[insertData.itemCount].assign(buffer);
				}
				insertData.itemCount++;
				parseState = INSERT_INTO_KEYVALUE;
			}
			break;
		case INSERT_INTO_RB:
			if(i == argc)
			{
				SQLInsert(insertData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SELECT:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "*")
			{
				parseState = SELECT_STAR;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SELECT_FROM:
			if(i == argc)
			{
				parseState = ERROR_TABLENAME_REQUIRED;
			}
			else
			{
				selectData.tableName.assign(strs[i]);
				parseState = SELECT_FROM_TABLENAME;
			}
			break;
		case SELECT_FROM_TABLENAME:
			if(i == argc)
			{
				SQLSelect(selectData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else if(strs[i] == "where")
			{
				parseState = SELECT_FROM_WHERE;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SELECT_FROM_WHERE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				selectData.condition[selectData.itemCount].keyName.assign(strs[i]);
				parseState = SELECT_FROM_KEYNAME;
			}
			break;
		case SELECT_FROM_KEYNAME:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "<")
			{
				selectData.condition[selectData.itemCount].comptype = LESS_THAN;
				parseState = SELECT_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == "<=")
			{
				selectData.condition[selectData.itemCount].comptype = LESS_EQUAL;
				parseState = SELECT_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == "=" || strs[i] == "==")
			{
				selectData.condition[selectData.itemCount].comptype = EQUAL;
				parseState = SELECT_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == ">=")
			{
				selectData.condition[selectData.itemCount].comptype = GREATER_EQUAL;
				parseState = SELECT_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == ">")
			{
				selectData.condition[selectData.itemCount].comptype = GREATER_THAN;
				parseState = SELECT_FROM_COMPARISON_TYPE;
			}
			else if(strs[i] == "!=" || strs[i] == "<>")
			{
				selectData.condition[selectData.itemCount].comptype = NOT_EQUAL;
				parseState = SELECT_FROM_COMPARISON_TYPE;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SELECT_FROM_COMPARISON_TYPE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				unsigned int result;

				selectData.condition[selectData.itemCount].dataValue.assign(strs[i]);
				result = GetType(selectData.condition[selectData.itemCount].dataValue);
				selectData.condition[selectData.itemCount].dataType = result;
				if((result & BIT_CHARS) != 0)
				{
					strcpy(buffer, selectData.condition[selectData.itemCount].dataValue.data());
					buffer[strlen(buffer) - 1] = 0;
					strcpy(buffer, buffer + 1);
					selectData.condition[selectData.itemCount].dataValue.assign(buffer);
				}
				selectData.itemCount++;
				parseState = SELECT_FROM_KEYVALUE;
			}
			break;
		case SELECT_FROM_KEYVALUE:
			if(i == argc)
			{
				SQLSelect(selectData);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else if(strs[i] == "and")
			{
				parseState = SELECT_FROM_AND;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SELECT_FROM_AND:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				selectData.condition[selectData.itemCount].keyName.assign(strs[i]);
				parseState = SELECT_FROM_KEYNAME;
			}
			break;
		case SELECT_STAR:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "from")
			{
				parseState = SELECT_FROM;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SHOW:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else if(strs[i] == "index")
			{
				parseState = SHOW_INDEX;
			}
			else if (strs[i] == "indices")
			{
				parseState = SHOW_INDICES;
			}
			else if(strs[i] == "table")
			{
				parseState = SHOW_TABLE;
			}
			else if(strs[i] == "tables")
			{
				parseState = SHOW_TABLES;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SHOW_INDEX:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				indexName = strs[i];
				parseState = SHOW_INDEX_INDEXNAME;
			}
			break;
		case SHOW_INDEX_INDEXNAME:
			if(i == argc)
			{
				ShowIndex(indexName);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SHOW_INDICES:
			if(i == argc)
			{
				ShowIndex();
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SHOW_TABLE:
			if(i == argc)
			{
				parseState = ERROR_NOT_ENOUGH_PARAMETER;
			}
			else
			{
				tableName = strs[i];
				parseState = SHOW_TABLE_TABLENAME;
			}
			break;
		case SHOW_TABLE_TABLENAME:
			if(i == argc)
			{
				ShowTable(tableName);
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		case SHOW_TABLES:
			if(i == argc)
			{
				ShowTable();
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
			}
			else
			{
				parseState = ERROR_SYNTAX;
			}
			break;
		default:
			{
				cout<<"EXCEPTION:The execution encountered unknown state and terminated unexpectedly."<<endl;
				for(int j = 0; j < sizeof(strs) / sizeof(string); j++)
				{
					strs[j].~string();
				}
				return false;
				break;
			}
		}
		i++;
	}
}

#endif /* _INTERPRETER_CPP_ */
