//bismillahir rahmanir rahim
#include<stdio.h>
int conditioncheck(int i);
struct node{
	int row;
	int coloumn;
	int value;

};
int a[9][9],count[9]={0};
struct node b[81];
int main()
{
	printf("This is a SUDOKU SOLVER.\nPlease provide input and put the unknown/s as 0.\n");
	int i,j,k=0,l=1;

	freopen("input.txt","r",stdin);

	for(i=0;i<9;i++)                            
		for(j=0;j<9;j++)
		{
			printf("(%d,%d) = ",i+1,j+1);

			scanf("%d",&a[i][j]);                  //taking inputs in a[i][j]

			if(a[i][j]<0 || a[i][j]>9)              //validity checking for any value >9 or <0 
			{                     
				printf("Invalid Input\n");
				return 0;
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
	{                                   //for checking every b[1] to b[k]
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
					return 0;
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
	for(i=0;i<9;i++)
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
				printf("%d %d\n",i,count[i]);
				printf("Invalid Input");
				return 0;
			}
		}


	printf("\nThe Solution is:\n\n");

	for(i=0;i<9;i++)                   //printing the solution.
	{
		for(j=0;j<9;j++)
		{
			printf("%d ",a[i][j]);
			if(j%3==2)
				printf(" ");
		}
		printf("\n");
		if(i%3==2)
			printf("\n");
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
// i have found only one bug ,if u enter any invalid sudoku (i.e. same value in row,coloumn,box) without any unknowns it cannot
// find it .so it will reprint the same given sudoku. 
