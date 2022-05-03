#include <stdio.h>
#include "mfhdf.h"
#include "hdf.h"
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"                  
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_LMAGENTA   "\033[01;35m"
#define ANSI_COLOR_GOLDEN	"\033[22;33m"

extern int row, col;

void write_data(char *L1B_out,float *data, char *sds_name)
{	int32 sd_id, sds_id, istat, sds_index;
	int32 start[2],edges[2];
	
	start[0] = 0;  /* index of first row to write */
	start[1] = 0;  /* index of first column to write */
	edges[0] = row;    /* the number of rows to write */
	edges[1] = col;    /* the number of cols to write */
	
	
		sd_id = SDstart(L1B_out, DFACC_WRITE);
	if (sd_id != FAIL)
		printf (ANSI_COLOR_MAGENTA"\n\t\t... %s opened to WRITE\n"ANSI_COLOR_RESET,L1B_out);
	else
		{	printf (ANSI_COLOR_MAGENTA"\n\t\t... access to WRITE %s FAILED\n"ANSI_COLOR_RESET,L1B_out);
			exit(1);
		}
	
	
	sds_index = SDnametoindex(sd_id, sds_name);	
	sds_id = SDselect (sd_id, sds_index);
	
	if (sds_id == FAIL)
		{	printf (ANSI_COLOR_MAGENTA"\n\t\t... unable to create %s in L1B file %s\n"ANSI_COLOR_RESET,sds_name, L1B_out);
			exit(1);
		}
	else
		printf (ANSI_COLOR_MAGENTA"\n\t\t... Writing %s\n"ANSI_COLOR_RESET,sds_name);

	istat = SDwritedata(sds_id, start, NULL, edges, (VOIDP)data); 
	if (istat != FAIL)
		printf (ANSI_COLOR_MAGENTA"\n\t\t... DATA is written to %s of L1B file %s\n"ANSI_COLOR_RESET,sds_name,L1B_out);
	else
		{	printf (ANSI_COLOR_MAGENTA"\n\t\t... unable to write DATA to %s of L1B file %s\n"ANSI_COLOR_RESET,sds_name,L1B_out);
			exit(1);
		}

	istat = SDendaccess(sds_id);
	if (istat == FAIL) {
       printf (ANSI_COLOR_MAGENTA"\n\t\t... unable to END access to %s of L1B file %s\n"ANSI_COLOR_RESET,sds_name,L1B_out);
		exit (-1);
	}	

	istat = SDend(sd_id);
	if (istat == FAIL) {
       printf (ANSI_COLOR_MAGENTA"\n\t\t... unable to CLOSE L1B file %s\n"ANSI_COLOR_RESET,L1B_out);
		exit (-1);
	}	
	else
		printf (ANSI_COLOR_MAGENTA"\n\t\t... CLOSED L1B file %s\n"ANSI_COLOR_RESET,L1B_out);
		
}
#undef ANSI_COLOR_RED     
#undef ANSI_COLOR_GREEN  
#undef ANSI_COLOR_YELLOW  
#undef ANSI_COLOR_BLUE                    
#undef ANSI_COLOR_MAGENTA 
#undef ANSI_COLOR_CYAN    
#undef ANSI_COLOR_RESET  
#undef ANSI_COLOR_LMAGENTA   
#undef ANSI_COLOR_GOLDEN	

