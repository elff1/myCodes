#ifndef _DBCLIENT_H_
#define _DBCLIENT_H_

#include "HashStorage.h"

class DBClient{
private:
	HashStorage* HashTable;
public:
	/**默认构造,hash空间为1<<21,数据文件为data */
	DBClient();
	
	/**hash空间为cap,数据文件名为fname */
	DBClient(int cap, char* fname);
	
	/**我是析构... */
	~DBClient();
	
	/**调用HashStorage的load(), 建立hash表, 若没有本地文件不会建表(return false),请用dbInsert和dbSync*/ 	
	bool dbBuild();
	
	/**批量插入*/
	bool dbInsert(SimReco* records, int size);
	
	/**批量查询(应该是一个样本文件的所有点对的key值数组
		size是数组大小(1000左右)
		values_size数组 是每个hash值对应的value数量(不会很多...)
		values数组 是每个hash值对应的value数组,一级指针需要学长new一下
		用完查询结果以后学长需要把一级和二级指针都delete掉...*/ 
		
	bool dbQuery(Key* keys, int size, int* values_size, Value** values);	
	
	/**调用HashStorage的dump(),把新插入的乐纹写入本地文件*/ 	
	bool dbSync();
	
	/**HashStorage的clear(),删表但不删除本地文件*/ 
	bool dbClear();
};

#endif
