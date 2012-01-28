/* Note:Your choice is C IDE */
#define XX			1   
#define YY			2
#define ZZ			3
#define xx		   -1   
#define yy		   -2
#define zz		   -3

#include <dos.h>
#include <math.h>
#include <alloc.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "mouse.h" 

int hit(char);
void draw_cube(void);
void showcube(void);
void faceCW(char);
void faceCCW(char);
void rotateCW(char);
void rotateCCW(char);

void body(char ch)
{
	extern first;
	int code,i,error=1;
	float small_big_ratio=1;
	
	if(first==0)
	{
		hide_mouse();
		draw_cube();
		show_mouse();
	}
	first=1;
	code=hit(ch);
	error=1;
	switch(code)
	{
		case XX:
		case YY:
		case ZZ:
		case xx:
		case yy:
		case zz:  
			error=0;
			break;
		default:
			break;
	}
	if(error==0){
			draw_cube();
		}
		
	showcube();
} 

int hit(char code)
{
	switch(code)
	{
		case 'x':
			return(xx); 
		case 'y':
			return(yy);
		case 'z':
			return(zz);
		case 'X':
			return(XX);
		case 'Y':
			return(YY);
		case 'Z':
			return(ZZ);
	}
	return(-11);
}

/* »æ³öÄ§·½ÂÖÀª */
void draw_cube(void)
{
    int i,x0=255,y0=215,dx=24,dy1=17,dy2=24;
	
	hide_mouse(); 
	setcolor(BLUE);
	
    for(i=0;i<=3;i++){
    line(x0,y0-i*dy2,x0-3*dx,y0-3*dy1-i*dy2);
    line(x0,y0-i*dy2,x0+3*dx,y0-3*dy1-i*dy2);
    line(x0-i*dx,y0-3*dy2-i*dy1,x0+3*dx-i*dx,y0-3*dy1-3*dy2-i*dy1);
    line(x0+i*dx,y0-3*dy2-i*dy1,x0-3*dx+i*dx,y0-3*dy1-3*dy2-i*dy1);
    line(x0-i*dx,y0-i*dy1,x0-i*dx,y0-3*dy2-i*dy1);
    line(x0+i*dx,y0-i*dy1,x0+i*dx,y0-3*dy2-i*dy1);
    }

	  show_mouse();
}
