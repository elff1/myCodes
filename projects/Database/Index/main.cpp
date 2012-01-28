//#include "BPTree.h"
#include "testBPTree.h"
#include <assert.h>
#include <time.h>

// Buffer
BaseNode blocks[BlockNum];

// Catalog
bool blockUsed[BlockNum];
int indexRootBlockId[IndexNum];
int indexDataBlockId[IndexNum];
DataType indexType[IndexNum];

int main(void){
	int i, j, tmp;
	const int size = 10;
	vector<int>::iterator vi;
	Address a;
	TKey ans;
	BaseNode *p = NULL;
	int data[size] = {5, 2, 7, 1, 9, 4, 0, 6, 3, 8};
	vector<int> v(data, data+size);
	vector<int> vn;
	time_t t_start, t_end;

	// Initialize
	for(i = 0; i < BlockNum; i++)
		blockUsed[i] = false;
	for(i = 0; i < IndexNum; i++)
		indexRootBlockId[i] = -1;
	for(i = 0; i < IndexNum; i++)
		indexDataBlockId[i] = -1;
	for(i = 0; i < IndexNum; i++)
		indexType[i] = TYPE_INT;
	
	for(i = 0; i < DATA_NUM; i++)
		vn.push_back(i);
	srand((unsigned int)time(0));
	for(i = 0; i < DATA_NUM; i++){
		j = rand() % DATA_NUM;
		tmp = vn.at(j);
		vn.erase(vn.begin() + j);
		vn.push_back(tmp);
	}
	/*for(i = 0; i < DATA_NUM; i++){
		cout << vn.at(i) << ' ';
	}
	system("pause");
	return 0;*/

	// test
	try{
		cout << "----------------insert " << DATA_NUM << " numbers----------------------" << endl;
		time(&t_start);
		//for(i = 0; i < 15; i++){
		//for(i = DATA_NUM; i >= 0; i--){
		for(vi = vn.begin(); vi != vn.end(); vi++){
			i = *vi;
			if(!(i % (DATA_NUM / PRINT_NUM)))
				cout << "-------------insert " << i << "---------------" << endl;
			try{
				a = InsertIndex(0, 0, TKey(i));
			}
			catch(ErKeyNotFound &e){
				cout << e.what() << e.key() << endl;
			}
			catch(DbEr &e){
				cout << e.what() << endl;
			}
			//p = (BaseNode *)GetBlock(a.blockId);

			//cout << "Insert Data Block: " << a.blockId << endl;

			//p->data[a.offset] = i;

			//PrintIndex(GetRootBlockId(0), p);
			//PrintCatalog();
		}
		time(&t_end);
		cout << "Run time for insert " << DATA_NUM << " data: " << t_end - t_start << "s" << endl;
		//PrintData(0, p);
		//PrintIndex(GetRootBlockId(0), p);

		cout << "----------------query " << DATA_NUM << " numbers----------------------" << endl;
		time(&t_start);
		//for(i = 0; i <= DATA_NUM; i++){
		for(vi = vn.begin(); vi != vn.end(); vi++){
			i = *vi;
			if(!(i % (DATA_NUM / PRINT_NUM)))
				cout << "-------------query " << i << "----------------" << endl;
			try{
				a = FindIndex(0, 0, TKey(i));
				p = (BaseNode *)GetBlock(a.blockId);
				ans = TKey(p->Key(a.offset), p->type);
				if(ans.iKey != i){
					throw ErKeyNotFound(TKey(i));
				}
			}
			catch(ErKeyNotFound &e){
				cout << e.what() << e.key() << endl;
			}
			catch(DbEr &e){
				cout << e.what() << endl;
			}

			//PrintIndex(GetRootBlockId(0), p);
			//PrintCatalog();
		}
		time(&t_end);
		cout << "Run time for query " << DATA_NUM << " data: " << t_end - t_start << "s" << endl;
		PrintCatalog();

		cout << "----------------delete " << DATA_NUM << " numbers----------------------" << endl;
		time(&t_start);
		//for(i = 0; i <= DATA_NUM; i++){
		for(vi = vn.begin(); vi != vn.end(); vi++){
			i = *vi;
			if(!(i % (DATA_NUM / PRINT_NUM)))
				cout << "-------------delete " << i << "---------------" << endl;
			try{
				DeleteIndex(0, 0, TKey(i));
			}
			catch(ErKeyNotFound &e){
				cout << e.what() << e.key() << endl;
			}
			catch(DbEr &e){
				cout << e.what() << endl;
			}

			//PrintIndex(GetRootBlockId(0), p);
			//PrintData(GetDataBlockId(0), p);
			//PrintCatalog();
		}
		time(&t_end);
		cout << "Run time for delete " << DATA_NUM << " data: " << t_end - t_start << "s" << endl;

		PrintData(GetDataBlockId(0), p);
		DropIndex(0, 0);
		PrintCatalog();
		/*for(i = 0; i < 15; i++){
			a = FindIndex(0, i);
			cout << "Find \"" << i << "\" in offset " << a.offset
				<< " of Block " << a.blockId << endl;
		}*/
	}
	catch(ErKeyNotFound &e){
		cout << e.what() << e.key() << endl;
	}
	catch(DbEr &e){
		cout << e.what() << endl;
	}

	system("pause");
}