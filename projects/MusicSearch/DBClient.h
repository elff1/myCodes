#ifndef _DBCLIENT_H_
#define _DBCLIENT_H_

#include "HashStorage.h"

class DBClient{
private:
	HashStorage* HashTable;
public:
	/**Ĭ�Ϲ���,hash�ռ�Ϊ1<<21,�����ļ�Ϊdata */
	DBClient();
	
	/**hash�ռ�Ϊcap,�����ļ���Ϊfname */
	DBClient(int cap, char* fname);
	
	/**��������... */
	~DBClient();
	
	/**����HashStorage��load(), ����hash��, ��û�б����ļ����Ὠ��(return false),����dbInsert��dbSync*/ 	
	bool dbBuild();
	
	/**��������*/
	bool dbInsert(SimReco* records, int size);
	
	/**������ѯ(Ӧ����һ�������ļ������е�Ե�keyֵ����
		size�������С(1000����)
		values_size���� ��ÿ��hashֵ��Ӧ��value����(����ܶ�...)
		values���� ��ÿ��hashֵ��Ӧ��value����,һ��ָ����Ҫѧ��newһ��
		�����ѯ����Ժ�ѧ����Ҫ��һ���Ͷ���ָ�붼delete��...*/ 
		
	bool dbQuery(Key* keys, int size, int* values_size, Value** values);	
	
	/**����HashStorage��dump(),���²��������д�뱾���ļ�*/ 	
	bool dbSync();
	
	/**HashStorage��clear(),ɾ����ɾ�������ļ�*/ 
	bool dbClear();
};

#endif
