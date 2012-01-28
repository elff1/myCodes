/**
* @file
* @brief the head file of the miniSQL
* @author elf@ZJU
* @version 1.0
*
* @TODO output the error index/block ID
* @change
*	1. add NOTFOUND
*	2. add Enums.h
*/

#ifndef _miniSQL_H
#define _miniSQL_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstring>
#include <queue>
#include <vector>
#include "TKey.h"

using namespace std;

//#define DEBUG
#define NDEBUG
#define buffer_size 10000
#define filename "database"
#define BlockNum 10000
#define IndexNum 10
#define DATA_LEN 4000
#define M 4
#define DATA_NUM 100000
#define PRINT_NUM 10

/** @def define the most numbers of attribute*/
#define MaxAttri 32
/** @def define the most length of string*/
#define MaxStrLen 255
/** @def define the most length of identifier name*/
#define MaxIdentLen 50
/** @def define the not found value*/
#define NOTFOUND -1

#define MAX_CMD_LENGTH  (255)
#define MAX_LINE_LENGTH (64)
#define MAX_ARG_NUMBER  (32)

#define TABLE_ID_START 5000
#define INDEX_ID_START 6000
#define KEY_ID_START   7000
#define MAX_ITEM_NUM   (32)//the maximal number of conditions or keys
#define NOT_FOUND      (-1)

enum ComparisonType//definition for relational operator
{
	LESS_THAN = 0,
	LESS_EQUAL,
	EQUAL,
	GREATER_EQUAL,
	GREATER_THAN
};

enum DataType//definition for data type
{
	TYPE_CHARS = 0,
	TYPE_FLOAT,
	TYPE_INT
};

enum ExecuteState
{
	STREAM_INPUT = 0,
	FILE_INPUT
};

enum ParseState
{
	INITIAL = 0,
	CLEAR,
	CREATE,
	CREATE_TABLE,
	CREATE_TABLE_TABLENAME,
	CREATE_TABLE_LB,
	CREATE_TABLE_KEYNAME,
	CREATE_TABLE_KEYTYPE,
	CREATE_TABLE_UNIQUE,
	CREATE_TABLE_KEYNAME_COMMA,
	CREATE_TABLE_CHAR,
	CREATE_TABLE_CHAR_LB,
	CREATE_TABLE_CHAR_SIZE,
	CREATE_TABLE_CHAR_RB,
	CREATE_TABLE_PRIMARY,
	CREATE_TABLE_PRIMARY_KEY,
	CREATE_TABLE_PRIMARY_KEY_LB,
	CREATE_TABLE_PRIMARY_KEY_KEYNAME,
	CREATE_TABLE_PRIMARY_KEY_RB,
	CREATE_TABLE_RB,
	CREATE_INDEX,
	CREATE_INDEX_INDEXNAME,
	CREATE_INDEX_ON,
	CREATE_INDEX_TABLENAME,
	CREATE_INDEX_LB,
	CREATE_INDEX_KEYNAME,
	CREATE_INDEX_RB,
	DELETE,
	DELETE_FROM,
	DELETE_FROM_TABLENAME,
	DELETE_FROM_WHERE,
	DELETE_FROM_KEYNAME,
	DELETE_FROM_COMPARISON_TYPE,
	DELETE_FROM_KEYVALUE,
	DELETE_FROM_AND,
	DROP,
	DROP_TABLE,
	DROP_TABLE_TABLENAME,
	DROP_INDEX,
	DROP_INDEX_INDEXNAME,
	ERROR_FILENAME_REQUIRED,
	ERROR_INDEXNAME_NOT_FOUND,
	ERROR_INDEXNAME_REQUIRED,
	ERROR_INVALID_VALUE,
	ERROR_KEY_ALREADY_EXISTS,
	ERROR_KEYLIST_REQUIRED,
	ERROR_KEYNAME_NOT_FOUND,
	ERROR_NOT_ENOUGH_PARAMETER,
	ERROR_PRIMARY_KEY_NOT_FOUND,
	ERROR_SYNTAX,
	ERROR_TABLENAME_NOT_FOUND,
	ERROR_TABLENAME_REQUIRED,
	ERROR_TOO_MANY_CONDITIONS,
	ERROR_TOO_MANY_KEYS,
	ERROR_UNKNOWN_COMMAND,
	ERROR_UNKNOWN_DATATYPE,
	EXECFILE,
	HELP,
	HELP_CREATE,
	HELP_DELETE,
	HELP_DROP,
	HELP_EXECFILE,
	HELP_INSERT,
	HELP_SELECT,
	HELP_SHOW,
	INSERT,
	INSERT_INTO,
	INSERT_INTO_TABLENAME,
	INSERT_INTO_VALUES,
	INSERT_INTO_LB,
	INSERT_INTO_KEYVALUE,
	INSERT_INTO_COMMA,
	INSERT_INTO_RB,
	SELECT,
	SELECT_FROM,
	SELECT_FROM_TABLENAME,
	SELECT_FROM_WHERE,
	SELECT_FROM_KEYNAME,
	SELECT_FROM_COMPARISON_TYPE,
	SELECT_FROM_KEYVALUE,
	SELECT_FROM_AND,
	SELECT_STAR,
	SELECT_STAR_FROM,
	SELECT_STAR_FROM_TABLENAME,
	SHOW,
	SHOW_INDEX,
	SHOW_INDEX_INDEXNAME,
	SHOW_INDICES,
	SHOW_TABLE,
	SHOW_TABLE_TABLENAME,
	SHOW_TABLES
};

/**
* @class DbEr
* @brief the base exception class of miniSQL//, inheriting from the exception
*/
class DbEr{// : public exception{
protected:
	char *info;
	TKey m_key;
public:
	DbEr(){info = NULL;};
	char *what(){return info;}
	TKey key(){return m_key;}
};

/**
* @class ErCreateFile
* @brief the create file exception
*/
class ErCreateFile : public DbEr{
public:
	ErCreateFile(char *str = "Can't create file "){info = str;}
};

/**
* @class ErCreateTable
* @brief the create table exception
*/
class ErCreateTable : public DbEr{
public:
	ErCreateTable(char *str = "Can't create table "){info = str;}
};

/**
* @class ErDeleteFile
* @brief the delete file exception
*/
class ErDeleteFile : public DbEr{
public:
	ErDeleteFile(char *str = "Can't delete file "){info = str;}
};

/**
* @class ErOpenFile
* @brief the open file exception
*/
class ErOpenFile : public DbEr{
public:
	ErOpenFile(char *str = "Can't open file"){info = str;}
};

/**
* @class ErWriteFile
* @brief the write file exception
*/
class ErWriteFile : public DbEr{
public:
	ErWriteFile(char *str = "Can't write file"){info = str;}
};

/**
* @class ErKeyNotFound
* @brief the record not found exception
*/
class ErKeyNotFound : public DbEr{
public:
	ErKeyNotFound(TKey key, char *str = "Can't find key "){
		info = str;
		m_key = key;
	}
};

/**
* @class ErUnknownCom
* @brief the unknown command exception
*/
class ErUnknownCom : public DbEr{
public:
	ErUnknownCom(char *str = "Unknown command"){info = str;}
};

/**
* @class ErBadNull
* @brief the bad null column exception
*/
class ErBadNull : public DbEr{
public:
	ErBadNull(char *str = "Can't be null of column "){info = str;}
};

/**
* @class ErTableExists
* @brief the table existing exception
*/
class ErTableExists : public DbEr{
public:
	ErTableExists(char *str = "The table exists"){info = str;}
};

/**
* @class ErUnknownTable
* @brief the unknown table exception
*/
class ErUnknownTable : public DbEr{
public:
	ErUnknownTable(char *str = "Unknown table "){info = str;}
};

/**
* @class ErUnknownColumn
* @brief the unknown column exception
*/
class ErUnknownColumn : public DbEr{
public:
	ErUnknownColumn(char *str = "Unknown column "){info = str;}
};

/**
* @class ErTooLongIdent
* @brief the too long identifier name exception
*/
class ErTooLongIdent : public DbEr{
public:
	ErTooLongIdent(char *str = NULL){
		if(!str){
			char temp[10];
			str = new char(40);
			strcpy(str, "Indentifier name is too long, the max length is ");
			itoa(MaxIdentLen, temp, 10);
			strcat(str, temp);
			info = str;
		}
	}
};

/**
* @class ErDupColumn
* @brief the duplicate column name exception
*/
class ErDupColumn : public DbEr{
public:
	ErDupColumn(char *str = "Duplicate column name "){info = str;}
};

/**
* @class ErDupKey
* @brief the duplicate key name exception
*/
class ErDupKey : public DbEr{
public:
	ErDupKey(char *str = "Duplicate key name "){info = str;}
};

/**
* @class ErEmptyQuery
* @brief the empty query exception
*/
class ErEmptyQuery : public DbEr{
public:
	ErEmptyQuery(char *str = "Query was empty"){info = str;}
};

/**
* @class ErMultiPriKey
* @brief the multiple primary key exception
*/
class ErMultiPriKey : public DbEr{
public:
	ErMultiPriKey(char *str = "Multiple primary key defined"){info = str;}
};

/**
* @class ErTooManyKeys
* @brief the too many keys specified exception
*/
class ErTooManyKeys : public DbEr{
public:
	ErTooManyKeys(char *str = "Too many keys specified, only one key allowed"){info = str;}
};

/**
* @class ErKeyNotExist
* @brief the key not existing exception
*/
class ErKeyNotExist : public DbEr{
public:
	ErKeyNotExist(char *str = "Key column does not exist"){info = str;}
};

/**
* @class ErIndexNotExist
* @brief the index not existing exception
*/
class ErIndexNotExist : public DbEr{
public:
	ErIndexNotExist(char *str = "Index does not exist"){info = str;}
};

/**
* @class ErBlockNotExist
* @brief the block not existing exception
*/
class ErBlockNotExist : public DbEr{
public:
	ErBlockNotExist(char *str = "Block does not exist"){info = str;}
};

/**
* @class ErUnknownError
* @brief the unknown error exception
*/
class ErUnknownError : public DbEr{
public:
	ErUnknownError(char *str = "Unknown error"){info = str;}
};

/**
* @class ErLackColumn
* @brief the lacking columns in table exception
*/
class ErLackColumn : public DbEr{
public:
	ErLackColumn(char *str = "A table must have one column"){info = str;}
};

/**
* @class ErTooManyColumns
* @brief the too many columns exception
*/
class ErTooManyColumns : public DbEr{
public:
	ErTooManyColumns(char *str = "Too many columns"){info = str;}
};

/**
* @class ErSyntax
* @brief the syntax error exception
*/
class ErSyntax : public DbEr{
public:
	ErSyntax(char *str = "Syntax error"){info = str;}
};

/**
* @class ErLogIndexRead
* @brief the reading log index file exception
*/
class ErLogIndexRead : public DbEr{
public:
	ErLogIndexRead(char *str = "Reading log index file error"){info = str;}
};

/**
* @class ErSQLFile
* @brief the opening SQL file exception
*/
class ErSQLFile : public DbEr{
public:
	ErSQLFile(char *str = "Unable to open the SQL file"){info = str;}
};

/**
* @class ErQuit
* @brief the quit exception
*/
class ErQuit : public DbEr{
public:
	ErQuit(char *str = "Bye"){info = str;}
};

class ErLock : public DbEr{
public:
	ErLock(char *str = "All blocks in buffer are locked!"){info = str;}
};

class ErPrintPointer : public DbEr{
public:
	ErPrintPointer(char *str = "No pointer in leaf!"){info = str;}
};

//int main(){
//	ercreatefile e;
//	exception("Can't create file")
//	e.what();
//	exception e;
//	cout << e.
//}

#endif // _miniSQL_H