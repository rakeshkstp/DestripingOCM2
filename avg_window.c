#include <stdio.h> 
#include <stdlib.h>
#include "mfunc.h"
#include <math.h>

extern int col;

float gstdev(float x[], int len);

float gavg(float x[], int len);

float igcoef(float x[],float C[], int len);


void ifgauss(float x[], int len)
{	int c,i;
	float *C,*pix,csum=0;
	float y=0;
		
	pix = (float *)calloc(len,sizeof(float));
	C = (float *)calloc(len,sizeof(float));
	
	for(c=0;c<col;c++)
	{	for(i=-len/2;i<=len/2;i++)
		{	if(c+i>=0 && c+i<col) 
				pix[i+len/2]=x[c+i];
			else if(c+i<0)
				pix[i+len/2]=0;//x[0];
			else if(c+i>col-1)
				pix[i+len/2]=0;//x[col-1];
		}			
		
		y=0;
		
		if(igcoef(pix,C,len)!=0)
		{	csum=0;
				
			for(i=-len/2;i<=len/2;i++)
			{	if(pix[len/2]==0)
				{	x[c]=0;				//y[c]
					csum=1;
					break;
				}
				else
				{	if(pix[i+len/2]!=0)	
					{	y+=C[i+len/2]*pix[i+len/2];
						csum+=C[i+len/2];
					}
				}
			}		
			y/=csum;
			x[c]=y;			//not here
		}
		else
			x[c]=0;
	}
	
	free(pix);
	free(C);
}

float igcoef(float x[], float C[], int len)
{ 	int i;
	float sum=0,c1;
	float sigma=gstdev(x,len);
     
    if(sigma!=0)  
	{	c1=sigma*sqrt(2.0*M_PI); 
		   
		for(i=-len/2;i<=len/2;i++)
		{	C[i+len/2]=1/(1+(c1*exp(-0.5*pow(((float)i)/sigma,2))));
			sum+=C[i+len/2];
		}
	}
	
	return sigma;
}


float gavg(float x[], int len)
{	float average,sum=0;
	int i,count=0;
	
	for (i = 0; i < len; i++)
        if(x[i]!=0)
		 {	sum += x[i];
			 count++;
		 }
	 	 
	if(count>0)
		average = sum / (float)count;
    else
		average=0;
	
	return average;
}


float gstdev(float x[], int len)
{	float average,sdev,sum=0;
	int i,count=0;
	
	average=gavg(x,len);
	
	for (i = 0; i < len; i++)
		if(x[i]!=0)
		{  sum += pow((x[i] - average), 2);
			count++;
		}
	
	if(count>0)
		sdev = sqrt(sum / (float)count);
	else
		sdev=0;
	
	return sdev;
}





