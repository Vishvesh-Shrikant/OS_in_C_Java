#include <stdio.h>
#define max_pr 50
#define max_bl 50

int blocks[max_bl], process[max_pr], allocation[max_pr], pr=0, bl=0, tempBlocks[max_bl];

void reset()
{ 
    /*used to reset the allocation and blocks array to the original values
    after each algorithm is run, so that the next algorithm can run on the original values*/
    int i;
    for(i=0; i<pr;i++)
        allocation[i]=-1; //resets the allocation array to -1
    
    for(i=0;i<bl;i++)
        blocks[i]= tempBlocks[i]; //resets the blocks array to the original values
}

void printAllocation()
{//used to print the allocation of the various processes
    int i;
    printf("\nProcess No. \t Block\n");
    for(i=0;i<pr;i++)
    {
        printf("%d \t\t ", i+1);
        if(allocation[i]==-1)
            printf("Not allocated\n");
        else
            printf("%d\n", allocation[i]+1);
    }
}

void displayHoleSize()
{ //displays the left over gaps in the memory blocks
    int i;
    printf("Block No. \t Hole Size\n");
    for(i=0;i<bl;i++)
    {
        printf("%d \t\t %d\n", i+1, blocks[i]);
    }
}

void firstFit ()
{
    int i, j;
    
    for(i=0;i<pr;i++)
    {
        for(j=0;j< bl;j++)
        {
            if (blocks[j] >= process[i])
            {//alocates memory to the first block of memory that process can fit in 
                allocation[i]= j; 
                blocks[j] -= process[i];
                break;
            }
        }
    }
    
    printAllocation();
    displayHoleSize();
}

void bestFit()
{
    int i, j, best;
    for(i=0;i< pr;i++)
    {   
        best = -1;
        for(j=0;j<bl;j++)
        {
            if(blocks[j] >= process[i])
            { 
                /*finds the best memory block , i.e block which is > processSize, 
                but lesser than all other blocks with size > process size */
                
                if( best==-1 || blocks[j]< blocks[best])
                    best=j;
            }
        }
        if(best != -1)
        { //allocations the process to best meory block 
            allocation[i]= best;
            blocks[best] -= process[i];
        }
    }
    
    printAllocation();
    displayHoleSize();
}

void worstFit()
{
    int i,j, worst;
    for(i=0;i<pr;i++)
    {
        worst = -1;
        for(j=0; j<bl;j++)
        {
            if(blocks[j] >= process[i])
            {
                /*finds the worst memory block , i.e block which is > processSize, 
                and greater than all other blocks with size > process size */
                if( worst == -1 || blocks[j]> blocks[worst])
                    worst =j;
            }
        }
        if (worst != -1)
        {
            allocation[i]= worst;
            blocks[worst] -= process[i];
        }
    }
    printAllocation();
    displayHoleSize();
}

void nextFit()
{
    int i,j, last=0, count=0;
    for( i=0; i< pr; i++)
    {
        j= last;
        count=0; 
        // count: used to keep ensure that for a process , we dont traverse more than no. of blocks
        while ( count < bl)
        {
            if(blocks[j] >= process[i])
            {
                
                allocation[i]= j; //finds a block and allocates the process
                blocks[j] -= process[i]; 
                last = j; //stores the block for to begin the finding from this block 
                break;
            }
            j = (j+1)% bl; //increments to the next block , %m to loop over the blocks
            count++; 
        }
    }
    printAllocation();
    displayHoleSize();
}


int main()
{
    int i;
    printf("\nEnter the no. of blocks: ");
    scanf("%d", &bl);
    printf("Enter the no. of processes: ");
    scanf("%d", &pr);
    
    printf("\nEnter block sizes: \n");
    for( i=0; i<bl; i++)
    {
        scanf("%d", &blocks[i]);
        tempBlocks[i]= blocks[i];
    }

    printf("\nEnter Process Sizes: \n");
    for( i=0; i< pr; i++)
    {
        scanf("%d", &process[i]);
    }
    
    reset();
    printf("\nFirst Fit:\n");
    firstFit();
    
    reset();
    printf("\nWorst Fit:\n");
    worstFit();
    
    reset();
    printf("\nNext Fit:\n");
    nextFit();
    
    reset();
    printf("\nBest Fit:\n");
    bestFit();

    return 0;
}
