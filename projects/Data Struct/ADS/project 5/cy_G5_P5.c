/*
* cy_G5_P5.c - the program for Research Project 5 of Advanced Data Structures and Algorithm Analysis.
* Copyright (C) Zhao Bingqian of Group 5. All rights reserved.
* Purpose: Print out the differences of two files in diff-like format.
* Algorithm: Using dynamic programming to get the LCS of the two files.
* Notice: The line number of each file should no larger than 50,
*		and the characters in a line should no more than 80.
* Instructor: Chen Yue.
* Version: 2011/1/3
*/
#include<stdio.h>
#include<string.h>

#define MaxLength 4500		/*The largest number of characters in a file.*/
#define LineLength 85		/*The largest number of characters in a line.*/

/*String is the string array to store the whole charaters of a file.*/
typedef char String[MaxLength+1];
/*Line is the string array to store a line*/
typedef char Line[LineLength+1];
/*PathArray is the array to store the state trasition path.*/
typedef int PathArray[MaxLength*2+2];
/*Matrix is the dynamic array to store the length of the states.*/
typedef int **Matrix;

/*The prior declaration of the functions.*/
void LCS_Length(String x, String y, int lx, int ly, Matrix c);
void GetPath(String x, String y, Matrix c, int i, int j, int k, PathArray path, int *NextLine);
void Print_Diff(String x, String y, PathArray path, int PathLen);
void PrintChar(char c);
void PrintLine(int k);

int main(){
	/*string x,y store the characters of the two files.*/
	String x, y;
	/*TempStr is used to get a whole line of a file while inputting.*/
	Line TempStr;
	/*c is the dynamic array that store the state value.*/
	Matrix c;
	/*path is the array that store the state transition path.*/
	PathArray path;
	/*
	*ComNum is the whole matched characters number, including the newline.
	*NextLine is the matched newline number.
	*PathLen is the length of the state transition path.
	*/
	int ComNum, NextLine, PathLen;
	/*
	*lx,ly are the length of the two file.
	*n,m are the line number of the two file.
	*/
	int lx, ly, n, m;
	int i, j, k;
	
	/*New a space for dynamic array c.*/
	c=(Matrix)malloc((MaxLength+1)*sizeof(int*));
	for(i=0;i<=MaxLength;i++)
		c[i]=(int*)malloc((MaxLength+1)*sizeof(int));

	/*Read in the first file line number n first.*/
	scanf("%d",&n);
	/*If n is negative, stop read in new cases.*/
	while(n>=0){
		/*Read in the second file line number m.*/
		scanf("%d",&m);
		getchar();

		/*Handling the special cases.*/
		if(!m&&!n){
			puts("No difference found");
			scanf("%d",&n);
			continue;
		}
		if(!m||!n){
			puts("Totally different");
			m+=n;
			for(i=0;i<m;i++)
				fgets(TempStr,LineLength-1,stdin);
			scanf("%d",&n);
			continue;
		}

		/*n and m is normal case, give the normal answers.*/
		/*Read the first file line by line and copy them to a string start from x[1].*/
		strcpy(x,"#");
		for(i=0;i<n;i++){
			fgets(TempStr,LineLength-1,stdin);
			strcat(x,TempStr);
		}
		lx=strlen(x)-1;

		/*Read the second file line by line and copy them to a string start from x[1].*/
		strcpy(y,"#");
		for(i=0;i<m;i++){
			fgets(TempStr,LineLength-1,stdin);
			strcat(y,TempStr);
		}
		ly=strlen(y)-1;

		/*Calculate the length of the LCS.*/
		LCS_Length(x,y,lx,ly,c);
		/*Get the whole common characters number.*/
		ComNum=c[lx][ly];
		/*Calculate the length of state transition path.*/
		PathLen=lx+ly-ComNum;

		/*Record the state transition path, and count the common newline number.*/
		NextLine=0;
		path[0]=0;
		path[PathLen+1]=1;
		x[0]=y[0]=0;
		GetPath(x,y,c,lx,ly,PathLen,path,&NextLine);
		
		/*Print out the answer as required.*/
		if(!(ComNum-NextLine))
			puts("Totally different");
		else if(ComNum==lx&&ComNum==ly)
			puts("No difference found");
		else{
			printf("%d\n",ComNum-NextLine);
			Print_Diff(x,y,path,PathLen);
		}

		/*Read in the next n.*/
		scanf("%d",&n);
	}

	/*Free the space of dynamic array c.*/
	for(i=0;i<=MaxLength;i++)
		free(c[i]);
	free(c);
}

/*
*Dynamic programming to calculate the length of LCS.
*/
void LCS_Length(String x, String y, int lx, int ly, Matrix c){
	int i, j;

	/*Initialize the edge state value.*/
	for(i=0;i<=lx;i++)
		c[i][0]=0;
	for(i=1;i<=ly;i++)
		c[0][i]=0;

	/*Dynamic programming the state value from small to large.*/
	for(j=1;j<=ly;j++)
		for(i=1;i<=lx;i++){
			if(x[i]==y[j]){
				c[i][j]=c[i-1][j-1]+1;
			}
			else
				if(c[i-1][j]>c[i][j-1]){
					c[i][j]=c[i-1][j];
				}
				else{
					c[i][j]=c[i][j-1];
				}
		}
}

/*
*Get the state trasition path, and count the common newline number.
*path[k]=0 means in the kth step, it goes upleft;
*path[k]=-1 means in the kth step, it goes legt;
*path[k]=1 means in the kth step, it goes up.
*/
void GetPath(String x, String y, Matrix c, int i, int j, int k, PathArray path, int *NextLine){
	/*Stop until reached c[0][0].*/
	while(i||j){
		/*Consider a special situlation.*/
		if(!path[k+1]&&x[i]==y[j]&&x[i+1]!='\n'&&x[i]!='\n'){
			/*Mark the path value as 0.*/
			path[k]=0;
			i--;
			j--;
			k--;
		}
		/*If it can go left, go left first.*/
		else if(j&&c[i][j]==c[i][j-1]){
			/*Mark the path value as -1.*/
			path[k]=-1;
			j--;
			k--;
		}
		/*Otherwise, if it can go up, then go up.*/
		else if(i&&c[i][j]==c[i-1][j]){
			/*Mark the path value as 1.*/
			path[k]=1;
			i--;
			k--;
		}
		/*Otherwise, it can go upleft only.*/
		else{
			/*Mark the path value as 0.*/
			path[k]=0;
			/*If the common character is a newline, count it.*/
			if(x[i]=='\n')(*NextLine)++;
			i--;
			j--;
			k--;
		}
	}
}

/*
*Print out the changes from the first file to the second.
*/
void Print_Diff(String x, String y, PathArray path, int PathLen){
	/*
	*Variable f mark the former print state.
	*Variable fl mark print state of a new line.
	*Variable line count the present line number.
	*/
	int i,j,k,f,fl,line;

	/*Print out the first line number.*/
	line=1;
	PrintLine(line);
	/*Initialize the flags.*/
	f=fl=0;
	/*
	*Print out one by one according to the path.
	*Start from x[1], y[1].
	*/
	i=j=0;
	for(k=1;k<=PathLen;k++){
		/*If they are common characters.*/
		if(!path[k]){
			i++;
			j++;
			/*If the former print a character to be deleted, ptint out a '-'.*/
			if(f>0)
				PrintChar('-');
			/*If the former print a character to be added, ptint out a '+'.*/
			else if(f<0)
				PrintChar('+');
			/*If the common character is a newline.*/
			if(x[i]=='\n'){
				/*If something printed in this line, turn to a new line.*/
				if(fl)
					PrintChar('\n');
				/*Print out the new line number.*/
				if(x[i+1]){
					line++;
					PrintLine(line);
				}
				/*Refresh the line flag.*/
				fl=0;
			}
			/*Refresh the print flag.*/
			f=0;
		}
		/*Otherwise, if a character should be deleted.*/
		else if(path[k]>0){
			/*If the former print is an added character, print out a '+'.*/
			if(f<0){
				PrintChar('+');
				/*Refresh the print flag.*/
				f=0;
			}
			i++;
			/*If the character to be added isn't a newline, print it out.*/
			if(x[i]!='\n'){
				PrintChar(x[i]);
				/*Mark the print flag and line flag.*/
				f=fl=1;
			}
			/*Otherwise, it's a newline.*/
			else{
				/*
				*If the former printed is deleted character, 
				*print out a '-' and turn to a new line.
				*/
				if(f){
					PrintChar('-');
					PrintChar('\n');
					/*Refresh the print flag.*/
					f=0;
				}
				/*Print out the new line number.*/
				if(x[i+1]){
					line++;
					PrintLine(line);
				}
				/*Refresh the line flag.*/
				fl=0;
			}
		}
		/*Otherwise, the character should be added.*/
		else{
			/*If the former print is a deleted character, print out a '-'.*/
			if(f>0){
				PrintChar('-');
				/*Refresh the print flag.*/
				f=0;
			}
			j++;
			/*If the character to added isn't a newline, print it out.*/
			if(y[j]!='\n'){
				PrintChar(y[j]);
				/*Mark the print flag and line flag.*/
				f=-1;
				fl=1;
			}
			/*Otherwise, it's a newline.*/
			else
				/*
				*If the former printed is added character, 
				*print out a '+' and turn to a new line.
				*/
				if(f){
					PrintChar('+');
					PrintChar('\n');
					/*Refresh the print flag and line flag.*/
					f=fl=0;
				}
		}
	}
}

/*Print out a single char.*/
void PrintChar(char c){
	putchar(c);
}

/*Print out the line number.*/
void PrintLine(int k){
	printf("line #%d:\n",k);
}