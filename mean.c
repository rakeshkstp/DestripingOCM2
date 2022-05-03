#include <stdio.h> 
#include <stdlib.h>

extern int row, col;

float mean_col(float x[], int ci,unsigned int cmask[])			//ci is column number
{  	int p,r;
	float k=0;
	float s=0.0;
	float m;
	
	k=0;
	for(r=0;r<row;r++)   //row
	{	p = r*col + ci;	//pixel
		if(cmask[p]==0)
		{	s+=x[p];
			k=k+1;
		}
	}
	
	if(k==0)
		m=0;
	else	 
		m=s/k;
	
	return m;	
}

float mean(float x[], int len)			//n is length of the input array
{  	int i;
	double s=0.0;
	float m;
	
		
	for(i=0;i<len;i++)   //row
		s+=x[i];
		
	m=s/len;

	return m;	
}


float mean_img(float x[],unsigned int mask[])			//n is length of the input array
{  	int r,c,p;
	double s=0.0;
	float m;
	double count=0;
			
	for(r=0;r<row;r++)   //row
		for(c=0;c<col;c++)   //row
		{	p=r*col+c;
			if(mask[p]==0)
			{	s+=x[p];
				count=count+1;
			}
		}
		
	m=s/count;

	return m;	
}
