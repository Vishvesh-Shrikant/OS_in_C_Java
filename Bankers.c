#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max_p 5
#define max_r 3

int total[max_r], allocated[max_p][max_r], maximum[max_p][max_r], need[max_p][max_r], available[max_r], safeSequence[max_p];
bool finish[max_p];


int main()
{
	int count=0, i, j; //count = no. of safe processes
	bool safe=false, canAllocate=true;
    
	//input for total resources
	printf("\nEnter total resources in order: \n");
	for( i=0; i<max_r; i++)
	{
		scanf("%d", &total[i]);
	}

	//input for allocated resources
	for( i=0; i<max_p; i++)
	{
		printf("Enter resources allocated to process %d\n", i+1);
		for(j=0; j< max_r; j++)
		{
			scanf("%d", &allocated[i][j]);
		}
	}

	//input for max_need of resources
	for( i=0; i<max_p; i++)
	{
		printf("Enter maximum resources required by process %d\n", i+1);
		for(j=0; j< max_r; j++)
		{
			scanf("%d", &maximum[i][j]);
			//computing need matrix
			need[i][j]= maximum[i][j] - allocated[i][j];
		}
	}

	// computing available resources
	for( i=0; i<max_r; i++)
	{
		available[i]= total[i];
		for(j=0; j< max_p; j++)
		{
			available[i] -= allocated[j][i];
		}
	}

	// is in safe state or not
	while ( count < max_p)
	{
		safe=false;
		for( i=0 ; i< max_p; i++)
		{
            if(!finish[i]) // check if the procecess is not finished
            {
                canAllocate=true;
                for ( j=0; j < max_r; j++)
			    {
    				if (available[j] < need[i][j])  
    				{//checks if the process can be allocted resources or not
    					canAllocate=false;
    					break;
    				}
			    }
			    if(canAllocate)
			    {
			        for ( j=0; j < max_r; j++)
			        {//add the process' allocated resources to available resources
			            available[j] += allocated[i][j];
			        }
			        safeSequence[count++]= i+1; //add process no. to safe sequence and increment count
			        safe= true; //mark the process as safe 
			        finish[i]=true; //mark process as finished
			    }
            }	
		}
        if(!safe)
        {
            break;
        }
	}
	
	if(count< max_p) //if not all processes are finished, then system is unsafe

	{
	    printf("\nTHE GIVEN SYSTEM OF PROCESSES IS UNSAFE.");
	}
	else
	{
	    printf("\nTHE GIVEN SYSTEM OF PROCESSES IS SAFE.\nSAFE SEQUENCE: \n");
	    for(i=0;i< max_p;i++)
	    {//print the safe sequence
	        printf("P%d\t", safeSequence[i]);
	    }
	}
	return 0;
}