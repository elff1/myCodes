#include "DBClient.h"

DBClient::DBClient(){

	HashTable = new HashStorage();
}

DBClient::DBClient(int cap, char* fname){
	//printf("%s\n",fname);

	HashTable = new HashStorage(cap, fname);
}

bool DBClient::dbBuild(){
	if(HashTable->load() != -1){
		return true;
	}
	return	false;
}

DBClient::~DBClient(){
	dbClear();
	delete HashTable;
}

bool DBClient::dbInsert(SimReco* records, int size){
	for(int i=0; i<size; i++){
		if(!(HashTable->insert(records[i], false))){
			return false;
		}
	}
	return true;
}

bool DBClient::dbQuery(Key* keys, int size, int* values_size, Value** values){
 
	for(int i=0; i<size; i++){

		values_size[i] = HashTable->count(keys[i]);
	 
		if(values_size[i] == 0) continue;
		else{
			values[i] = new Value[values_size[i]];

			std::vector<Value>::iterator iter;
			int k = 0;
 
			for(iter = (*HashTable)[keys[i]].begin(); iter!=(*HashTable)[keys[i]].end(); iter++){
		 
	/*			printf("%d %d %f\n",keys[i],  iter->trackID, iter->leftTime);*/
				values[i][k++] = (*iter);
			}	
		}	
	}
 
	return true;
}

bool DBClient::dbSync(){
	if(HashTable->dump() != -1 ){
		return true;
	}
	return false;
}

bool DBClient::dbClear(){
	HashTable->clear();
	return true;
}