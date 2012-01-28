#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include <fstream>
#include <iostream>
#include <string>
#include "Buffer.h"
#include "CatalogManager.h"
#include "Interpreter.h"
#include "miniSQL.h"

using namespace std;

CatalogInfo catalogInfo;

int main()
{
	bool inputCommandFile;
	bool inputCommandStream;
	bool exitProcess;
	int lineCounter;

	int argc;
	char args[MAX_ARG_NUMBER][MAX_ITEM_LENGTH];
	char line[MAX_LINE_LENGTH];
	char sqlcmd[MAX_CMD_LENGTH];
	ExecuteState executeState;
	ifstream SQLFile;
	string strs[MAX_ARG_NUMBER];
	const string catalogFileName = "DBCatalog.txt";

	ImportCatalog(catalogInfo, catalogFileName);
	InitBuffer();
	executeState = STREAM_INPUT;
	exitProcess = false;
	WelcomeInfo();
	while(exitProcess == false)
	{
		lineCounter = 0;
		for(int i = 0; i < MAX_ARG_NUMBER; i++)
		{
			args[i][0] = 0;
		}
		sqlcmd[0] = 0;

		if(SQLFile.is_open() == true)
		{
			executeState = FILE_INPUT;
		}
		else
		{
			executeState = STREAM_INPUT;
		}

		switch(executeState)
		{
		case STREAM_INPUT:
			{
				inputCommandStream = true;
				while(inputCommandStream == true)
				{
					if(lineCounter == 0)
						cout << "miniSQL> ";
					else
						cout << "       > ";
					line[0] = 0;
					inputCommandStream = GetLine(line, MAX_LINE_LENGTH, ';');
					if(strlen(line) > 0)
					{
						if(lineCounter > 0)
						{
							strcat(sqlcmd, " ");
						}
						strcat(sqlcmd, line);
						lineCounter++;
					}
				}
				//Execute the command
				Standardize(sqlcmd, ';');
				argc = CutString(sqlcmd, args, MAX_ARG_NUMBER);
				for(int i = 0; i < argc ; i++)
				{
					strs[i].assign(args[i]);
				}

				//Insert your TEST CODE here.
				//cout<<"argc = "<<argc<<endl;
				//for(int i = 0; i < argc ; i++)
				//{
				//	cout<<"strs["<<i<<"]:"<<strs[i]<<endl;
				//}
				//puts(sqlcmd);
				//Test code is OVER.
				try{
					exitProcess = ExecSQL(strs, argc, SQLFile);
				}
				catch (ErWrongType &e){
					cout << e.what() << e.key() << endl;
				}
				catch (DbEr &e)
				{
					cout<<e.what()<<endl;
				}
			}
			break;
		case FILE_INPUT:
			{
				inputCommandFile = true;
				while(inputCommandFile == true)
				{
					line[0] = 0;
					inputCommandFile = GetLineF(line, MAX_LINE_LENGTH, ';', SQLFile);
					if(strlen(line) > 0)
					{
						if(lineCounter > 0)
						{
							strcat(sqlcmd, " ");
						}
						strcat(sqlcmd, line);
						lineCounter++;
						if(strlen(line) > 0)
						{
							size_t i;

							for(i = 0; i < strlen(line); i++)
							{
								if(!isblank(line[i]))
									break;
							}
							if(i < strlen(line))
							{
							}
						}
					}
				}
				//Execute the command

				strcat(sqlcmd, ";");
				Standardize(sqlcmd, ';');
				argc = CutString(sqlcmd, args, MAX_ARG_NUMBER);

				for(int i = 0; i < argc ; i++)
				{
					strs[i].assign(args[i]);
				}

				if(strlen(sqlcmd) > 0)
				{
					size_t i;

					for(i = 0; i < strlen(sqlcmd); i++)
					{
						if(!isblank(sqlcmd[i]))
							break;
					}
					if(i < strlen(sqlcmd))
					{
						try
						{
							exitProcess = ExecSQL(strs, argc, SQLFile);
						}
						catch (ErWrongType &e){
							cout << e.what() << e.key() << endl;
						}
						catch (ErMorePara &e){
							cout<<e.what()<<endl;
							cout << sqlcmd << endl;
						}
						catch (DbEr &e)
						{
							cout<<e.what()<<endl;
						}
					}
				}

				if(SQLFile.peek() == EOF)
				{
					executeState = STREAM_INPUT;
					SQLFile.close();
				}
			}
			break;
		}
		putchar('\n');
	}
	BufferDispose();
	ExportCatalog(catalogInfo, catalogFileName);
	exit(0);
}

#ifdef DEBUG_GET_TYPE
int main()
{
	string str;

	while(1)
	{
		cin>>str;
		if(str.length() == 0)
			break;
		unsigned result;

		result = GetType(str);

		if((result & BIT_CHARS) != 0)
		{
			cout<<"char ";
		}
		if((result & BIT_FLOAT) != 0)
		{
			cout<<"float ";
		}
		if((result & BIT_INT) != 0)
		{
			cout<<"int ";
		}
		if(result == 0)
		{
			cout<<"error";
		}
		cout<<endl;
	}

	return 0;
}
#endif //DEBUG_GET_TYPE

#endif /* _MAIN_CPP_ */
