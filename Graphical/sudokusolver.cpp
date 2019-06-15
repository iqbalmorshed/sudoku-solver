//bismilalhir rahmair rahim
#include "iGraphics.h"
#include <stdlib.h>
#include<string.h>
struct node               
{
	int row;
	int coloumn;
	int value;

};
int a[9][9];
struct node b[81];

char n[81],c[81][2],c2[81][2];

int p=0,q,r=0,h=0,m=0,row=0;
int q2,r2=0,h2=0,m2=0,row2=0;
int i,z=0;
int mode=0;
int fmode=0;
int w=0;

//position of box (1,1)
#define ABSCISSA 24
#define ORDINATE 390

//difference between left side and right side of a sudoku box
int xdif=46;
int ydif=46;

//position of solution box (1,1)
#define ABSCISSA2 445
#define ORDINATE2 390

//difference between left side and right side of a solution sudoku box
int xdif2=46;
int ydif2=46;

int abscissa=ABSCISSA;
int ordinate=ORDINATE;

int abscissa2=ABSCISSA2;
int ordinate2=ORDINATE2;

/*
Function iDraw() is called again and again by the system.
*/
void sudokubox(int llx,int lly,int side)    //a function to create sudoku box
{
	iSetColor(0,255 , 0);
    iRectangle(llx,lly,side,side);
	
	int s;
	s=side/3;
	iSetColor(0, 255, 0);
	iRectangle(llx,lly,s,s);
    iRectangle(llx+s,lly,s,s);
    iRectangle(llx+s*2,6,s,s);
    iRectangle(llx,lly+s,s,s);
    iRectangle(llx,lly+s*2,s,s);
    iRectangle(llx+s,lly+s,s,s);
    iRectangle(llx+s*2,lly+s*2,s,s);
	
	int t;
	t=side/9;
	iSetColor(0, 0, 0);
	iLine(llx,lly+t,llx+side,lly+t);
	iLine(llx,lly+t*2,llx+side,lly+t*2);
	iLine(llx,lly+t*4,llx+side,lly+t*4);
	iLine(llx,lly+t*5,llx+side,lly+t*5);
	iLine(llx,lly+t*7,llx+side,lly+t*7);
	iLine(llx,lly+t*8,llx+side,lly+t*8);

	iLine(llx+t,lly,llx+t,lly+side);
	iLine(llx+t*2,lly,llx+t*2,lly+side);
	iLine(llx+t*4,lly,llx+t*4,lly+side);
	iLine(llx+t*5,lly,llx+t*5,lly+side);
	iLine(llx+t*7,lly,llx+t*7,lly+side);
	iLine(llx+t*8,lly,llx+t*8,lly+side);

}


void iDraw()
{
	iClear();

	iSetColor(255, 255, 255);
	iShowBMP(0,0, "bridge1.bmp");

	sudokubox(6,6,414);   //calling sudokubox function for creating sudoku box.
	sudokubox(430,6,414); //calling sudokubox function for creatin sudoku box

    iRectangle(106,446,110,50); //creating rectangle for "SOLVE"
    iRectangle(521,446,110,50); //creating rectangle for "STOP"
	
	iSetColor(255,255,255);
	iText(130,470,"SOLVE",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(540,470,"STOP",GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 0,0);

	for(q=0;q<p;q++)      //this loop will put input to the corresponding coordinate
	{
		if(q%9==0 && q!=0)
		{
			m=r;          //storing total increament in x-axis after completing one row
			row++;        //increasing row after one coloumn.
		}
		abscissa=ABSCISSA-m; //to start from the first box the row after completing previous row
		h=-ydif*row;        //changing height after completing each row.
		

		if(strcmp(c[q],"0")==0)          //special case for 0.              
			iText(abscissa+r,ordinate+h," " , GLUT_BITMAP_TIMES_ROMAN_24);   //instead of zero space will be printed
		else
			iText(abscissa+r,ordinate+h, c[q] , GLUT_BITMAP_TIMES_ROMAN_24); //	putting input c[] values to corresponding abscissa
																			//and ordinate		
		r=r+xdif;   //increasing in x-axis
	}
	abscissa=ABSCISSA;             //as idraw function is called again and again new initialization is required
	h=0;
	r=0;
	row=0;
	m=0;

	if( (fmode==1 && z==0 && mode==1) ||(p==81 && z==0 && mode ==1)) //if filemode is on ,result is valid and mode is on or  
	{                                                                //if all 81 boxes are filled
		for(q2=0;q2<81;q2++)
		{
			if(q2%9==0 && q2!=0)
			{
				m2=r2;
				row2++;

			}

			abscissa2=ABSCISSA2-m2;
			h2=-ydif2*row2;

			if(strcmp(c[q2],"0")==0)        // different colour for c2[] value if c[] value is 0.
				iSetColor(255, 0, 0);
			else
				iSetColor(255, 255, 255);

			iText(abscissa2+r2,ordinate2+h2, c2[q2] , GLUT_BITMAP_TIMES_ROMAN_24);//showing output
			r2=r2+xdif2;
		}
		abscissa2=ABSCISSA2;
		h2=0;
		r2=0;
		row2=0;
		m2=0;
	}
	if( (fmode==1 && z==1 && mode==1) ||(p==81 && z==1 && mode ==1)) //when result is invalid(i.e.z=0)
	{
		iSetColor(255,0,0);
		iText(269,484, "INVALID SUDOKU" , GLUT_BITMAP_TIMES_ROMAN_24);

	}


}
int conditioncheck(int i);
int calculatesudoku()                 //main sudoku solving function
{	
	int j,k=0,l=1,y=0,y2=0;
	int count[9]={0};

	if(fmode==1)                      // take input from file if file mode is open
		freopen("input.txt","r",stdin);
	
	for(i=0;i<9;i++)
	{                            
		for(j=0;j<9;j++)
		{
			if(fmode==1)             //when in file mode
			{
				scanf("%d",&a[i][j]);
				itoa(a[i][j],c[y++],10);   //transfer int to char
				p=y;
			}
			else
				a[i][j]=atoi(c[y++]);     // in keyboard mode
		}
	}

	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
		{
			if(a[i][j]==0)       //copying the unknown values(i.e. 0) to anther array of structure(i.e. b[k])
			{                         
				b[k].row=i;
				b[k].coloumn=j;
				b[k].value=0;
				k++;
			}
		}

	for(i=0;i<k;i++)
	{											//for checking every b[1] to b[k]
		for(j=l;j<=9;j++)        //for checking 1 to appropiate value (maximum 9) for every b[i].value
		{
			b[i].value=j;
			if(conditioncheck(i)==1)
			{
				a[b[i].row][b[i].coloumn]=b[i].value;     //copying b[i].value to a[][];
				l=1;                                      //for initialization of next b[k].value.
				break;
			}
			if(j==9)                                       //when all b[].value from 1 to 9 fails.... 
			{
				a[b[i].row][b[i].coloumn]=b[i].value=0;    //clearing b[].value and corrensponding a[][]
				i--;                                       //decrementing i for going to previous b[].value
				if(i==-1)                                  //error checking for any invalid sudoku where it will find value for b[0].value
				{
					printf("Invalid Sudoku\n");
					return 1;
				}
				if(b[i].value==9)                        //special case for b[].value=9
				{
					l=9;                //because it will be cleared when it will enter if(j==9)condition of previous b[].value
					i--;                //again decreamenting i to compansate increamenting in for loop.
					break;
				}
				l=b[i].value + 1;      //checking for b[].value from next value to 9                     
				i--;                    
				break;
			}

		}
	}

	for(i=0;i<9;i++)                  //counter for error checking
		{
			for(j=0;j<9;j++)
			{
				if(a[i][j]==1)
					count[0]++;
				else if(a[i][j]==2)
					count[1]++;
				else if(a[i][j]==3)
					count[2]++;
				else if(a[i][j]==4)
					count[3]++;
				else if(a[i][j]==5)
					count[4]++;
				else if(a[i][j]==6)
					count[5]++;
				else if(a[i][j]==7)
					count[6]++;
				else if(a[i][j]==8)
					count[7]++;
				else if(a[i][j]==9)
					count[8]++;
			}
		}
		for(i=0;i<9;i++)
		{
			if(count[i]!=9)
			{
				printf("Invalid Input\n");
				return 1;
			}
		}
		//for(i=0;i<9;i++)
			//count[i]=0;

	for(i=0;i<9;i++)                   //printing the solution to c2[]
	{
		for(j=0;j<9;j++)
		{
			itoa(a[i][j],c2[y2++],10);
		}
	}

	return 0;

}
int conditioncheck(int i)
{
	int j,k;
	for(j=0;j<9;j++)                   //checking row of a[][] whether same b[].value exists in the row or not
		if(a[b[i].row][j]==b[i].value)
			return 0;

	for(j=0;j<9;j++)                   //checking coloumn of a[][] whether same b[].value exists in the coloumn or not.
		if(a[j][b[i].coloumn]==b[i].value)
			return 0;

	if(b[i].row>=0 && b[i].row<=2 && b[i].coloumn>=0 && b[i].coloumn<=2)//checking box of a[][] whether same b[].value exists in the box or not.
	{
		for(j=0;j<=2;j++)
			for(k=0;k<=2;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}

	else if(b[i].row>=3 && b[i].row<=5 && b[i].coloumn>=0 && b[i].coloumn<=2)
	{
		for(j=3;j<=5;j++)
			for(k=0;k<=2;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=6 && b[i].row<=8 && b[i].coloumn>=0 && b[i].coloumn<=2)
	{
		for(j=6;j<=8;j++)
			for(k=0;k<=2;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=0 && b[i].row<=2 && b[i].coloumn>=3 && b[i].coloumn<=5)
	{
		for(j=0;j<=2;j++)
			for(k=3;k<=5;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=3 && b[i].row<=5 && b[i].coloumn>=3 && b[i].coloumn<=5)
	{
		for(j=3;j<=5;j++)
			for(k=3;k<=5;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=6 && b[i].row<=8 && b[i].coloumn>=3 && b[i].coloumn<=5)
	{
		for(j=6;j<=8;j++)
			for(k=3;k<=5;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=0 && b[i].row<=2 && b[i].coloumn>=6 && b[i].coloumn<=8)
	{
		for(j=0;j<=2;j++)
			for(k=6;k<=8;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=3 && b[i].row<=5 && b[i].coloumn>=6 && b[i].coloumn<=8)
	{
		for(j=3;j<=5;j++)
			for(k=6;k<=8;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}
	else if(b[i].row>=6 && b[i].row<=8 && b[i].coloumn>=6 && b[i].coloumn<=8)
	{
		for(j=6;j<=8;j++)
			for(k=6;k<=8;k++)
				if(a[j][k]==b[i].value)
					return 0;
	}

	return 1;

}


void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
		if(mx >= 106 && mx <= 106+110 && my >= 446 && my <= 446+50 && mode == 0)// if mouse presses the "SOLVE" button
		{
			mode = 1;
		}
		 if(mx >= 521 && mx <= 521+110 && my >= 446 && my <= 446+50 && mode == 1) //if mouse presses the "STOP" button
		{
			mode = 0;
		}

 		printf("%d %d\n", mx, my); //shows the mouse pointer co-ordinate

	}

}
void iKeyboard(unsigned char key)
{
	if(key=='c')
	{
		p=0;
	}
	else if(key=='f')   //for file input
	{
		fmode=1;
		z=calculatesudoku();
	}

	else if(key=='\b') //for backspace key
		p--;

	else if(key==' ')  // for space key
	{
		fmode=0;  		            
		c[p][0]='0'; 		//we will take 'spaces' as zero.
		c[p][1]='\0';
		p++;
	}

	else
	{
		fmode=0;
		c[p][0]=key;     //	storing key in input array c[][]
		c[p][1]='\0';
		p++;
	}
	
	if(p==81)
	{
		fmode=0;
		z=calculatesudoku();
	}
	if(key==27)
	{
		exit(0);
	}
}
void iSpecialKeyboard(unsigned char key)
{
}

int main()
{
	//place your own initialization codes here before iInitialize().
	iInitialize(1280, 700, "sudoku.txt");
	return 0;
}
