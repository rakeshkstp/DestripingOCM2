#include <stdlib.h>
#include <stdio.h> 
#include "mfunc.h"

extern int row,col;

void inv_water_mask(float nir[],unsigned int mask[])
{	int r,c,p;
	
	for(r=0;r<row;r++)
		for(c=0;c<col;c++)
		{	p=r*col+c;
			if(nir[p]>2)
				mask[p]=1;
			else
				mask[p]=0;	
		}
}
