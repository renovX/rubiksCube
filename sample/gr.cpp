#include<stdio.h>

#include<graphics.h>

void flood(int,int,int,int);
void main()
{
int gd,gm=DETECT;
clrscr();
detectgraph(&gd,&gm);
initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
rectangle(60,60,90,90);
flood (50,50,8,0);
getch();
}
void flood(int a,int b, int fcol, int col)
{
if(getpixel(a,b)==col)
{
delay(15);
putpixel(a,b,fcol);
flood(a+1,b,fcol,col);
flood (a-1,b,fcol,col);
flood (a,b+1,fcol,col);
flood (a,b-1,fcol,col);
}
}