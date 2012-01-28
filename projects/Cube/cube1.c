/* Note:Your choice is C IDE */
#define VERSION "Version 1.0"

#define F		0	/* Front face 前面 */ 
#define R		1	/* Right face 右面 */
#define T		2	/* Top face 上面 */
#define H		3	/* beHind face后面 */
#define L		4	/* Left face 左侧面 */
#define B		5	/* Bottom face 下面 */

#define CW  	-1	/* clockwise 顺时针 */
#define CCW  	-2	/* counterclockwise 逆时针 */ 

#define ESC  	27	/* Esc的键值 */
#define F1  	59	   
#define F2  	60
#define F3  	61
#define F4  	62
#define F5  	63
#define F6  	64

#define ON  	1
#define OFF  	0

#include <stdio.h>
#include <dos.h> 
#include <alloc.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include<time.h>
#include "mouse.h"

void body(char);
char getmousech(MOUSE *);
void to_graphic_mode(void);
void initialize(void);
void arrange(void);
void handle(char);
void showcube(void);
void savegame(void);
void loadgame(void);
void soundswitch(void);
int win(void);
void showlist(void); 
int quit(void);
void restart(void);
void draw_win(void);   
void sink(int,int,int,int,int);
void mem_error(void);
void file_error(char *);
void show_version(int,int,int);
void clr_kb_buff(void); 
void sinkkey(char);   
void help(void);
void message(int,char *); 
void cubesound(void);  
void faceCW(char);
void faceCCW(char);
void rotateCW(char);
void rotateCCW(char);

int first=0;        /* 检查是不是第一次绘制魔方画面 */

MOUSE mouse;        /* 定义鼠标变量 */
int soundflag=ON;   /* 声音开关标记，初值为ON */
int mu_install=OFF; /* 鼠标使用标记，初值为OFF */
int check_win=0;
time_t start,end;
int time_now=1000;
char date_now[20]="0000/00/00";
int sq[6][9];         /* 魔方方块的颜色 */

int color[]={WHITE,RED,CYAN,YELLOW,DARKGRAY,GREEN};

/* 初始化可看到的面即前、右和上面的颜色 */

/* 定义鼠标可移动区域和相应的键值 */
struct mu_click
{
	int cl,ct,cr,cb;  /* left,top,right,bottom,即鼠标的左、上、右、下的区域 */
	char key;         /* 区域内相应键值 */
}def_click[]=
{
	{ 18+(65+1)*0,253,  18+(65+1)*0+64,  253+44, 'f'},
	{ 18+(65+1)*1,253,  18+(65+1)*1+64,  253+44, 'h'},
	{ 18+(65+1)*2,253,  18+(65+1)*2+64,  253+44, 'r'},
	{ 18+(65+1)*3,253,  18+(65+1)*3+64,  253+44, 'l'},
	{ 18+(65+1)*4,253,  18+(65+1)*4+64,  253+44, 't'},
	{ 18+(65+1)*5,253,  18+(65+1)*5+64,  253+44, 'b'}, 
	{ 426+(65+1)*0,253, 426+(65+1)*0+64,  253+44,'x'}, 
	{ 426+(65+1)*1,253, 426+(65+1)*1+64,  253+44,'y'},
	{ 426+(65+1)*2,253, 426+(65+1)*2+64,  253+44,'z'},
	
	{ 18+(65+1)*0,253+46,  18+(65+1)*0+64,  253+44+46, 'F'},
	{ 18+(65+1)*1,253+46,  18+(65+1)*1+64,  253+44+46, 'H'},
	{ 18+(65+1)*2,253+46,  18+(65+1)*2+64,  253+44+46, 'R'},
	{ 18+(65+1)*3,253+46,  18+(65+1)*3+64,  253+44+46, 'L'},
	{ 18+(65+1)*4,253+46,  18+(65+1)*4+64,  253+44+46, 'T'},
	{ 18+(65+1)*5,253+46,  18+(65+1)*5+64,  253+44+46, 'B'},
	{ 426+(65+1)*0,253+46, 426+(65+1)*0+64, 253+44+46, 'X'},
	{ 426+(65+1)*1,253+46, 426+(65+1)*1+64, 253+44+46, 'Y'},
	{ 426+(65+1)*2,253+46, 426+(65+1)*2+64, 253+44+46, 'Z'},
	
	{526,62+(21+7)*0,526+80,62+(21+7)*0+20,F2}, 
	{526,62+(21+7)*1,526+80,62+(21+7)*1+20,F3}, 
	{526,62+(21+7)*2,526+80,62+(21+7)*2+20,F4}, 
	{526,62+(21+7)*3,526+80,62+(21+7)*3+20,F5}, 
	{526,62+(21+7)*4,526+80,62+(21+7)*4+20,F6}
};

/***********main()*********/

void main(void)
{
	int i,j;
	char ch=0;
	
		if(strcmp(getenv("HAVE_CUBE"),"YES")==0)
		{
			printf("\nMagic Cube has already executed!\n");
			printf("Type EXIT to return to Magic Cube...\n");
			exit(1);
		}

	to_graphic_mode();	
	draw_win();
	ch=0;
	check_win=0;
	arrange();
	start=time(NULL);

	body(ch);
	showcube();
	clr_kb_buff();
	do{
		ch=-1;
		if(!kbhit())
		{
			if(click_button(&mouse,LEFT_B))
				ch=getmousech(&mouse);
		}
		else
			ch=getch();
		handle(ch);
		if(ch!=-1)
			body(ch);
	}while(!win());
closegraph();

}
/*******************End of main()******************/

/* 初始化图形函数 */
void to_graphic_mode(void)
{
	int gdriver=DETECT,gmode=EGA,errorcode;
	
	initgraph(&gdriver,&gmode,""); 
	errorcode=graphresult();
 	if(errorcode!=grOk)
	{
		printf("\nGraphic System Error:%s\n",grapherrormsg(errorcode));
		exit(1);
	}
}

/* 初始化鼠标函数 */
void initialize(void)
{
	extern unsigned Cursor[][32];
	delay(1);
	init_mouse();
	set_graphic_cursor(5,1,Cursor[0]);
	show_mouse();
}

/* 魔方预处理 */
void arrange()
{
	int i,j,rand_n;
	time_t t;
	char c;

	/* 给魔方块分配颜色 */
	for(i=0;i<6;i++)
    for(j=0;j<9;j++)
			sq[i][j]=color[i];
	srand((unsigned)time(&t));
	for(i=0;i<10;i++){
		rand_n=random(100);
		if(rand_n<75){
			switch(random(6)){
				case 0:c='f';break;
				case 1:c='h';break;
				case 2:c='r';break;
				case 3:c='l';break;
				case 4:c='t';break;
				case 5:c='b';break;
			}
			faceCW(c);
		}else{
			switch(random(3)){
				case 0:c='x';break;
				case 1:c='y';break;
				case 2:c='z';break;
			}
			rotateCW(c);
		}
	}
}

/* 绘制游戏主界面 */
void draw_win(void)
{
	char *helptext="F1 for help";
	char buffer[80];
	FILE *fp;
	int i,j;
	int width=65,hight=45;
	char *facekey[][6]={"f","h","r","l","t","b",
						"F","H","R","L","T","B"};
  char *cubekey[][3]={"x","y","z","X","Y","Z"};
  char *helpkey[]={"F2","F3","F4","F5","F6"};
  
	setcolor(GREEN);
	for(i=0;i<2;i++)
	{
		for(j=0;j<6;j++)
		{
			outtextxy(18+j*(width+2)+2,253+(hight+2)*i+2,facekey[i][j]);
			}
		for(j=0;j<3;j++)
		{
			outtextxy(426+j*(width+2)+2,253+(hight+2)*i+2,cubekey[i][j]);
			}
	}
	for(i=0;i<5;i++)
		outtextxy(526+2,62+28*i+2,helpkey[i]);
	outtextxy(526+2,62-28+2,helptext);
	show_version(524,243,RED);  
	show_mouse();
}

/*  重绘三个可见面的颜色  */
void showcube(void)
{
	int i,j;
		FILE *fp;

	int pt[][9][2]={
		{255,45,279,62,303,79,  231,62,255,79,279,96,  207,79,231,96,255,113},
		{188,97,212,114,236,131,  188,121,212,138,236,155,  188,145,212,162,236,179},
		{260,148,284,126,308,109,  260,186,284,169,308,152,  260,210,284,193,308,176}
		};
		
	setcolor(BLUE);
	hide_mouse();
	for(i=0;i<3;i++)
		for(j=0;j<5;j++)
		{
			setfillstyle(SOLID_FILL,sq[i][j]);
			floodfill(pt[i][j][0],pt[i][j][1],BLUE);
			setfillstyle(SOLID_FILL,sq[i][8-j]);
			floodfill(pt[i][8-j][0],pt[i][8-j][1],BLUE);
		}
	show_mouse();
} 

/* 处理功能键 */
void handle(char ch)
{	
	sinkkey(ch);
	switch(ch)
	{
		case 't':
		case 'T':
		case 'f':
		case 'F':
		case 'r':
		case 'R':
		case 'l':
		case 'L':
		case 'h':
		case 'H':
		case 'b':
		case 'B':
			if(islower(ch))
				faceCW(ch);
			else
			{
				ch=tolower(ch);
				faceCCW(ch);
			}
			break;
		case 'x':
		case 'X':
		case 'y':
		case 'Y':
		case 'z':
		case 'Z': 
			if(islower(ch))
				rotateCW(ch);
			else
			{
				ch=tolower(ch);
				rotateCCW(ch); 
			}
			break;
		case F1:
			help();
			break; 
		case F2:
			savegame();
			break; 
		case F3:
			loadgame();
			break;
		case F4:
			showlist();
			break;
		case F5:
			soundswitch();
			break;
		case F6:
			restart();
			break;
		case ESC:
			if(quit()){
				closegraph();
				exit(1);
			}
			break;
		default:;
	}
}

char getmousech(MOUSE *mu1)
{
	int k;
	
	for(k=0;k<(sizeof(def_click)/sizeof(struct mu_click));k++)
		if((mu1->x>=def_click[k].cl)&&(mu1->x<=def_click[k].cr)&&
		   (mu1->y>=def_click[k].ct)&&(mu1->y<=def_click[k].cb))
		  return def_click[k].key;
}
		
/*  判定魔方是否还原成功,及成功后的相应操作 */
int win()
{
	struct date d;
	int i,j,col;
	for(i=0;i<6;i++){
		col=sq[i][0];
		for(j=1;j<9;j++)
			if(col!=sq[i][j])return(0);
	}
	end=time(NULL);
	time_now=difftime(end,start);
	getdate(&d);
	sprintf(date_now,"%d/%d/%d",d.da_year,d.da_mon,d.da_day);
	check_win=1;
	showlist();
	
	if(!quit())
	{
		restart();
		return 0;
	}
	else 
		return 1;
}

/*  显示简单的提示信息 */
void message(int color,char *msg)
{
	hide_mouse();
	setcolor(color);
	settextjustify(CENTER_TEXT,TOP_TEXT);
	outtextxy(200,20,msg);
	show_mouse();
}

/*  保存当前游戏状态 */
void savegame(void)
{
	int i,j;
	FILE *fp;
	char *filename="CUBE.SAV";
	char *savemsg="Saving...";
	
	if((fp=fopen(filename,"w"))==NULL)
		file_error(filename);
	message(3,savemsg);
	for(i=0;i<6;i++)
	{
		for(j=0;j<9;j++)
			fprintf(fp," %d",sq[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
	sleep(1);
	message(BLACK,savemsg);
}

/*  调入之前保存的游戏状态 */
void loadgame(void)
{
	int i,j;
	FILE *fp;
	char *filename="CUBE.SAV";
	
	if((fp=fopen(filename,"r"))==NULL)
	{
		sound(1000);
		delay(50);
		nosound();
		message(3,"Fail!");
		sleep(1);
		message(BLACK,"Fail!");
	}
	else
	{ 
		message(3,"Loading...");
		for(i=0;i<6;i++)
			for(j=0;j<9;j++)
				fscanf(fp,"%d",&sq[i][j]);
		fclose(fp);
		rotateCCW('x'); 
		rotateCCW('x');
		showcube();
		sleep(1);
		message(BLACK,"Loading..."); 
	}
}

/*  询问是否退出游戏 */
int quit(void)
{
	char ch;
	char *quitmsg="Do you want to continue to play?Y/N";
	message(RED,quitmsg);
	do{
		ch=getch();
	}while(!(ch=='Y'||ch=='N'||ch=='y'||ch=='n'));	
	message(BLACK,quitmsg);
	if(ch=='Y'||ch=='y')
		return 0;
	else
		return 1;
}

/*  重新开始游戏 */
void restart(void)
{
		arrange();
		cleardevice();
		draw_win();
		start=time(NULL);
		check_win=0;
		first=0;
		body(0);
		showcube();
		clr_kb_buff();
}

/* 添加显示排行榜 */
void showlist(void)
{
	int i,k,n=4,temp,index;
	char date_tmp[20];
	int record[4];
	char date[4][20];
	char s[4][10];
	FILE *fp;
	void *helpbuff;
	unsigned helpsize;
	
	hide_mouse();
	set_x_range(20,500);
	set_y_range(10,240);
	helpsize=imagesize(160,40,350,220);
	if((helpbuff=malloc(helpsize))==NULL)
	mem_error();
	getimage(160,40,350,220,helpbuff);
	setfillstyle(SOLID_FILL,BLACK);
	bar(100,40,380,220);
	
	if((fp=fopen("cube.lis","r"))==NULL){
		message(RED,"File open error!");
		sleep(1);
		message(BLACK,"File open error!");
	}
	for(i=0;i<3;i++){
	fscanf(fp,"%d%s",&record[i],date[i]);
	}
	fclose(fp);
	
	for(i=0;i<3;i++)
		sprintf(s[i], "%d", record[i]);		
	setcolor(RED);
	outtextxy(180,40,"Record");
	outtextxy(250,40,"Date");
	setcolor(LIGHTGRAY);
	for(i=0;i<3;i++){
	outtextxy(180,40+(2+textheight("H"))*(i+1),s[i]);
	outtextxy(250,40+(2+textheight("H"))*(i+1),date[i]);}
	if(check_win){
		check_win=0;
		record[3]=time_now;
		sprintf(s[3], "%d", record[3]);
		strcpy(date[3],date_now);
		if(time_now<record[2]){
			for(k=0;k<n-1;k++){
				index=k;
				for(i=k+1;i<n;i++)
					if(record[i]<record[index])index=i;
				temp=record[index];
				strcpy(date_tmp,date[index]);
				record[index]=record[k];
				strcpy(date[index],date[k]);
				record[k]=temp;
				strcpy(date[k],date_tmp);
			}
			setcolor(RED);
			outtextxy(180,40+(2+textheight("H"))*4,"A new record!");	
			setcolor(GREEN);
			outtextxy(180,40+(2+textheight("H"))*5,s[3]);
			outtextxy(250,40+(2+textheight("H"))*5,date_now);
			if((fp=fopen("cube.lis","w"))==NULL){
				message(RED,"File open error!");
				sleep(1);
				message(BLACK,"File open error!");
			}
			for(i=0;i<3;i++)
				fprintf(fp,"%d %s\n",record[i],date[i]);
			fclose(fp);
		}
		else{
			setcolor(RED);
			outtextxy(180,40+(2+textheight("H"))*4,"Come on!");	
			setcolor(GREEN);
			outtextxy(180,40+(2+textheight("H"))*5,s[3]);
			outtextxy(250,40+(2+textheight("H"))*5,date_now);
		}
	}
	show_mouse();
	while(!kbhit())
		if((mu_install)&&(which_pressed(&mouse)>0))
			break;
	hide_mouse();
	bar(100,40,500,250);
	putimage(160,40,helpbuff,COPY_PUT);
	free(helpbuff);
	clr_kb_buff();
	set_x_range(0,getmaxx());
	set_y_range(0,getmaxy()); 
	show_mouse();
}

/* 声音控制 */
void soundswitch(void)
{
	extern soundflag;
	char *soundmsg[]={"Sound Off","Sound On"};
	
	soundflag=(soundflag==ON)?OFF:ON;
	message(3,soundmsg[soundflag]);
	sleep(1);
	message(BLACK,soundmsg[soundflag]); 
}

void mem_error(void)
{
	closegraph();
	printf("\nOut of memory!\n");
	printf("Press any key to halt:");  
  getch();  
  exit(1);
}

void file_error(char *filename)
{
	closegraph();
	printf("\nCan not open file '%s'!\n",filename);
	printf("Press any key to halt:");  
  getch(); 
	exit(1);
}

void show_version(int x,int y,int color)
{
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setcolor(color);
	outtextxy(x,y,VERSION);
}

void clr_kb_buff(void)
{
	union REGS reg;
	
	reg.h.ah=0x0c;
	intdos(&reg,&reg);
}

/* 按键下陷 */
void sinkkey(char ch)
{
	int i;
	
	for(i=0;i<(sizeof(def_click)/sizeof(struct mu_click));i++)
		if(ch==def_click[i].key)
		{
			hide_mouse();
			sink(def_click[i].cl,def_click[i].ct,
			     def_click[i].cr,def_click[i].cb,OFF);
			show_mouse();
			while((mu_install)&&(which_pressed(&mouse)!=0));
			delay(100);
			hide_mouse();
			sink(def_click[i].cl,def_click[i].ct,
			     def_click[i].cr,def_click[i].cb,ON);
			show_mouse();
			cubesound();
		}
}

void sink(int left,int top,int right,int bottom,int status)
{
	setcolor((status==ON)?WHITE:BLUE);
	line(left,top,right,top);
	line(left,top,left,bottom); 
	
	setcolor((status==OFF)?WHITE:BLUE);
	line(right,bottom,right,top);
	line(right,bottom,left,bottom); 
}

/* 显示帮助 */
void help(void)
{
	int i;
	void *helpbuff;
	unsigned helpsize;
	char *helpmsg[]=
	{
		"F1:Help Menu",
		"F2:Save Game",
		"F3:Load Game",
		"F4:Show Record",
		"F5:Sound Switch",
		"F6:Restart Game",
		"Esc:Quit Game",
		" ",
		"f/F:rotate the left front face",
		"h/H:rotate the right back face",
		"r/R:rotate the right front face",
		"l/L:rotate the left back face",
		"t/T:rotate the upper face",
		"b/B:rotate the nether face",
		"x/X:rotate the cube on the X axis",
		"y/Y:rotate the cube on the Y axis",
		"z/Z:rotate the cube on the Z axis",
		"(the uppercase means clockwise",
		"the lowercase means anticlokwise)"
	};
	
	hide_mouse();
	set_x_range(20,500);
	set_y_range(10,240);
	helpsize=imagesize(160,40,500,250);
	if((helpbuff=malloc(helpsize))==NULL)
		mem_error();
	getimage(160,40,500,250,helpbuff);
	setfillstyle(SOLID_FILL,BLACK);
	bar(160,40,500,250);
	setcolor(LIGHTGRAY);
	for(i=0;i<sizeof(helpmsg)/sizeof(helpmsg[0]);i++)
		outtextxy(180,40+(2+textheight("H"))*i,helpmsg[i]);
	show_mouse();
	while(!kbhit())
		if((mu_install)&&(which_pressed(&mouse)>0))
			break;
	hide_mouse();
	bar(160,40,500,250);
	putimage(160,40,helpbuff,COPY_PUT);
	free(helpbuff);
	clr_kb_buff();
	set_x_range(0,getmaxx());
	set_y_range(0,getmaxy()); 
	show_mouse();
}

void cubesound(void)
{
	extern soundflag;
	
	if(soundflag)
	{
		sound(700);
		delay(20);
		nosound();
	}
}

/* 顺时针改变指定面的结构 */
void faceCW(char ch)
{
int temp[3],i;
switch(ch)
{
    case 'f':
        for(i=0;i<3;i++)
            temp[i]=sq[0][8-i];    
        for(i=0;i<3;i++){
            sq[0][8-i]=sq[5][2+3*i];
            sq[5][2+3*i]=sq[3][i];
            sq[3][i]=sq[2][6-3*i];
            sq[2][6-3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[1][i];
        for(i=0;i<2;i++){
            sq[1][i]=sq[1][6-3*i];
            sq[1][6-3*i]=sq[1][8-i];
            sq[1][8-i]=sq[1][2+3*i];
            sq[1][2+3*i]=temp[i];
        }
        break;
        
     case 'r':
        for(i=0;i<3;i++)
            temp[i]=sq[0][2+3*i];        
        for(i=0;i<3;i++){
            sq[0][2+3*i]=sq[1][2+3*i];
            sq[1][2+3*i]=sq[3][2+3*i];
            sq[3][2+3*i]=sq[4][6-3*i];
            sq[4][6-3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[2][i];
        for(i=0;i<2;i++){
            sq[2][i]=sq[2][6-3*i];
            sq[2][6-3*i]=sq[2][8-i];
            sq[2][8-i]=sq[2][2+3*i];
            sq[2][2+3*i]=temp[i];
        }
        break;
        
     case 't':
        for(i=0;i<3;i++)
            temp[i]=sq[4][i];            
        for(i=0;i<3;i++){
            sq[4][i]=sq[5][i];
            sq[5][i]=sq[1][i];
            sq[1][i]=sq[2][i];
            sq[2][i]=temp[i];
        }            
        for(i=0;i<2;i++)
        		temp[i]=sq[0][i];
        for(i=0;i<2;i++){
            sq[0][i]=sq[0][6-3*i];
            sq[0][6-3*i]=sq[0][8-i];
            sq[0][8-i]=sq[0][2+3*i];
            sq[0][2+3*i]=temp[i];
        }
        break;
        
     case 'l':
        for(i=0;i<3;i++)
            temp[i]=sq[0][6-3*i];            
        for(i=0;i<3;i++){
            sq[0][6-3*i]=sq[4][2+3*i];
            sq[4][2+3*i]=sq[3][6-3*i];
            sq[3][6-3*i]=sq[1][6-3*i];
            sq[1][6-3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[5][i];
        for(i=0;i<2;i++){
            sq[5][i]=sq[5][6-3*i];
            sq[5][6-3*i]=sq[5][8-i];
            sq[5][8-i]=sq[5][2+3*i];
            sq[5][2+3*i]=temp[i];
        }
        break;
        
     case 'b':
        for(i=0;i<3;i++)
            temp[i]=sq[1][8-i];            
        for(i=0;i<3;i++){
            sq[1][8-i]=sq[5][8-i];
            sq[5][8-i]=sq[4][8-i];
            sq[4][8-i]=sq[2][8-i];
            sq[2][8-i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[3][i];
        for(i=0;i<2;i++){
            sq[3][i]=sq[3][6-3*i];
            sq[3][6-3*i]=sq[3][8-i];
            sq[3][8-i]=sq[3][2+3*i];
            sq[3][2+3*i]=temp[i];
        }
        break;
        
     case 'h':
        for(i=0;i<3;i++)
            temp[i]=sq[0][i];            
        for(i=0;i<3;i++){
            sq[0][i]=sq[2][2+3*i];
            sq[2][2+3*i]=sq[3][8-i];
            sq[3][8-i]=sq[5][6-3*i];
            sq[5][6-3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[4][i];
        for(i=0;i<2;i++){
            sq[4][i]=sq[4][6-3*i];
            sq[4][6-3*i]=sq[4][8-i];
            sq[4][8-i]=sq[4][2+3*i];
            sq[4][2+3*i]=temp[i];
        }
        break;
        
     default:break;
}
}

/*  逆时针改变指定面的结构 */
void faceCCW(char ch)
{
int temp[3],i;
switch(ch)
{
    case 'f':
        for(i=0;i<3;i++)
            temp[i]=sq[0][8-i];    
        for(i=0;i<3;i++){
            sq[0][8-i]=sq[2][6-3*i];
            sq[2][6-3*i]=sq[3][i];
            sq[3][i]=sq[5][2+3*i];
            sq[5][2+3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[1][i];
        for(i=0;i<2;i++){
            sq[1][i]=sq[1][2+3*i];
            sq[1][2+3*i]=sq[1][8-i];
            sq[1][8-i]=sq[1][6-3*i];
            sq[1][6-3*i]=temp[i];
        }
        break;
        
     case 'r':
        for(i=0;i<3;i++)
            temp[i]=sq[0][2+3*i];        
        for(i=0;i<3;i++){
            sq[0][2+3*i]=sq[4][6-3*i];
            sq[4][6-3*i]=sq[3][2+3*i];
            sq[3][2+3*i]=sq[1][2+3*i];
            sq[1][2+3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[2][i];
        for(i=0;i<2;i++){
            sq[2][i]=sq[2][2+3*i];
            sq[2][2+3*i]=sq[2][8-i];
            sq[2][8-i]=sq[2][6-3*i];
            sq[2][6-3*i]=temp[i];
        }
        break;
        
     case 't':
        for(i=0;i<3;i++)
            temp[i]=sq[4][i];            
        for(i=0;i<3;i++){
            sq[4][i]=sq[2][i];
            sq[2][i]=sq[1][i];
            sq[1][i]=sq[5][i];
            sq[5][i]=temp[i];
        }            
        for(i=0;i<2;i++)
        		temp[i]=sq[0][i];
        for(i=0;i<2;i++){
            sq[0][i]=sq[0][2+3*i];
            sq[0][2+3*i]=sq[0][8-i];
            sq[0][8-i]=sq[0][6-3*i];
            sq[0][6-3*i]=temp[i];
        }
        break;
        
     case 'l':
        for(i=0;i<3;i++)
            temp[i]=sq[0][6-3*i];            
        for(i=0;i<3;i++){
            sq[0][6-3*i]=sq[1][6-3*i];
            sq[1][6-3*i]=sq[3][6-3*i];
            sq[3][6-3*i]=sq[4][2+3*i];
            sq[4][2+3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[5][i];
        for(i=0;i<2;i++){
            sq[5][i]=sq[5][2+3*i];
            sq[5][2+3*i]=sq[5][8-i];
            sq[5][8-i]=sq[5][6-3*i];
            sq[5][6-3*i]=temp[i];
        }
        break;
        
     case 'b':
        for(i=0;i<3;i++)
            temp[i]=sq[1][8-i];            
        for(i=0;i<3;i++){
            sq[1][8-i]=sq[2][8-i];
            sq[2][8-i]=sq[4][8-i];
            sq[4][8-i]=sq[5][8-i];
            sq[5][8-i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[3][i];
        for(i=0;i<2;i++){
            sq[3][i]=sq[3][2+3*i];
            sq[3][2+3*i]=sq[3][8-i];
            sq[3][8-i]=sq[3][6-3*i];
            sq[3][6-3*i]=temp[i];
        }
        break;
        
     case 'h':
        for(i=0;i<3;i++)
            temp[i]=sq[0][i];            
        for(i=0;i<3;i++){
            sq[0][i]=sq[5][6-3*i];
            sq[5][6-3*i]=sq[3][8-i];
            sq[3][8-i]=sq[2][2+3*i];
            sq[2][2+3*i]=temp[i];
        }
        for(i=0;i<2;i++)
        		temp[i]=sq[4][i];
        for(i=0;i<2;i++){
            sq[4][i]=sq[4][2+3*i];
            sq[4][2+3*i]=sq[4][8-i];
            sq[4][8-i]=sq[4][6-3*i];
            sq[4][6-3*i]=temp[i];
        }
        break;
        
     default:break;
}
}

/*  顺时针旋转魔方 */
void rotateCW(char ch)
{
    int i,temp[9];
            
    switch(ch)
    {
        case 'x':
        	for(i=0;i<9;i++)
        		temp[i]=sq[0][i];
        	for(i=0;i<9;i++){
        		sq[0][i]=sq[5][6-i%3*3+i/3];
        		sq[5][6-i%3*3+i/3]=sq[3][8-i];
        		sq[3][8-i]=sq[2][2+i%3*3-i/3];
        		sq[2][2+i%3*3-i/3]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[1][i];
        	for(i=0;i<2;i++){
            sq[1][i]=sq[1][6-3*i];
            sq[1][6-3*i]=sq[1][8-i];
            sq[1][8-i]=sq[1][2+3*i];
            sq[1][2+3*i]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[4][i];
        	for(i=0;i<2;i++){
            sq[4][i]=sq[4][2+3*i];
            sq[4][2+3*i]=sq[4][8-i];
            sq[4][8-i]=sq[4][6-3*i];
            sq[4][6-3*i]=temp[i];
        	}
          break;
            
        case 'y':
            for(i=0;i<9;i++)
                temp[i]=sq[0][i];                
            for(i=0;i<9;i++){
                sq[0][i]=sq[1][i];
                sq[1][i]=sq[3][i];
                sq[3][i]=sq[4][8-i];
                sq[4][8-i]=temp[i];
            }
                
            for(i=0;i<2;i++)
                temp[i]=sq[2][i];            
            for(i=0;i<2;i++){
                sq[2][i]=sq[2][6-3*i];
                sq[2][6-3*i]=sq[2][8-i];
                sq[2][8-i]=sq[2][2+3*i];
                sq[2][2+3*i]=temp[i];
            }
                
            for(i=0;i<2;i++)
            		temp[i]=sq[5][i];
            for(i=0;i<2;i++){
                sq[5][i]=sq[5][2+3*i];
                sq[5][2+3*i]=sq[5][8-i];
                sq[5][8-i]=sq[5][6-3*i];
                sq[5][6-3*i]=temp[i];
            }
        		break;
        	
        case 'z':
        	for(i=0;i<9;i++)
        		temp[i]=sq[1][i];
        	for(i=0;i<9;i++){
        		sq[1][i]=sq[2][i];
        		sq[2][i]=sq[4][i];
        		sq[4][i]=sq[5][i];
        		sq[5][i]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[0][i];
        	for(i=0;i<2;i++){
            sq[0][i]=sq[0][6-3*i];
            sq[0][6-3*i]=sq[0][8-i];
            sq[0][8-i]=sq[0][2+3*i];
            sq[0][2+3*i]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[3][i];
        	for(i=0;i<2;i++){
            sq[3][i]=sq[3][2+3*i];
            sq[3][2+3*i]=sq[3][8-i];
            sq[3][8-i]=sq[3][6-3*i];
            sq[3][6-3*i]=temp[i];
        	}
        	break;
    }
}

/* 逆时针旋转魔方 */
void rotateCCW(char ch)
{
    int i,temp[9];
            
    switch(ch)
    {
        case 'x':
        	for(i=0;i<9;i++)
        		temp[i]=sq[0][i];
        	for(i=0;i<9;i++){
        		sq[0][i]=sq[2][2+i%3*3-i/3];
        		sq[2][2+i%3*3-i/3]=sq[3][8-i];
        		sq[3][8-i]=sq[5][6-i%3*3+i/3];
        		sq[5][6-i%3*3+i/3]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[1][i];
        	for(i=0;i<2;i++){
            sq[1][i]=sq[1][2+3*i];
            sq[1][2+3*i]=sq[1][8-i];
            sq[1][8-i]=sq[1][6-3*i];
            sq[1][6-3*i]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[4][i];
        	for(i=0;i<2;i++){
            sq[4][i]=sq[4][6-3*i];
            sq[4][6-3*i]=sq[4][8-i];
            sq[4][8-i]=sq[4][2+3*i];
            sq[4][2+3*i]=temp[i];
        	}
          break;
            
        case 'y':
            for(i=0;i<9;i++)
                temp[i]=sq[0][i];                
            for(i=0;i<9;i++){
                sq[0][i]=sq[4][8-i];
                sq[4][8-i]=sq[3][i];
                sq[3][i]=sq[1][i];
                sq[1][i]=temp[i];
            }
                
            for(i=0;i<2;i++)
                temp[i]=sq[2][i];            
            for(i=0;i<2;i++){
                sq[2][i]=sq[2][2+3*i];
                sq[2][2+3*i]=sq[2][8-i];
                sq[2][8-i]=sq[2][6-3*i];
                sq[2][6-3*i]=temp[i];
            }
                
            for(i=0;i<2;i++)
            		temp[i]=sq[5][i];
            for(i=0;i<2;i++){
                sq[5][i]=sq[5][6-3*i];
                sq[5][6-3*i]=sq[5][8-i];
                sq[5][8-i]=sq[5][2+3*i];
                sq[5][2+3*i]=temp[i];
            }
        		break;
        	
        case 'z':
        	for(i=0;i<9;i++)
        		temp[i]=sq[1][i];
        	for(i=0;i<9;i++){
        		sq[1][i]=sq[5][i];
        		sq[5][i]=sq[4][i];
        		sq[4][i]=sq[2][i];
        		sq[2][i]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[0][i];
        	for(i=0;i<2;i++){
            sq[0][i]=sq[0][2+3*i];
            sq[0][2+3*i]=sq[0][8-i];
            sq[0][8-i]=sq[0][6-3*i];
            sq[0][6-3*i]=temp[i];
        	}
        	
        	for(i=0;i<2;i++)
        		temp[i]=sq[3][i];
        	for(i=0;i<2;i++){
            sq[3][i]=sq[3][6-3*i];
            sq[3][6-3*i]=sq[3][8-i];
            sq[3][8-i]=sq[3][2+3*i];
            sq[3][2+3*i]=temp[i];
        	}
        	break;
    }
}