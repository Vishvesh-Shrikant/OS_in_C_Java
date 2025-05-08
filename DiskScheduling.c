#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 7
#define disk 200

int requests[max]= {82, 170, 43, 140, 24, 16, 190};
int head;


void  fcfs( int head)
{
    int i,seek=0;
    for(i=0;i< max;i++)
    {
        printf("%d\t", requests[i]); //print the request being used
        seek += abs(head- requests[i]); // add absolute distance to sek time 
        head=requests[i]; //update head
    }
    
    printf("\nSeek time for FCFS is: %d\n\n", seek);
}

void sstf(int head)
{
    int i,j, seek=0, min, pos, temp[max], done[max];
    for(i=0;i< max;i++)
    {
        temp[i]= requests[i];
        done[i]=0;
    }
    
    for(i=0;i<max;i++)
    {
        min=9999, pos=0;
        for(j=0;j<max;j++)
        {
            if( done[j] == 0 && (abs(head-temp[j]) < min))
            {
                //finds the minimum seek time between two requests and assigns it to pos 
                min=abs(head-temp[j]);
                pos=j;
            }
        }
        printf("%d\t", temp[pos]);
        seek+= abs(head-temp[pos]);// adds the minimum seek time to the total seek time
        head=temp[pos]; // updates the head to the current request
        done[pos]=1;
    }
    printf("\nSeek time for SSTF is: %d\n\n", seek);
}

void scan( int head, int dir)
{
    int temp[max+2], pos, i,j, t, n=max, seek=0;
    for(i=0;i<n;i++)
    {
        temp[i]= requests[i];
    }
    temp[n++]=head; //adds the head to the request array
    temp[n++]= dir==0? 0: disk-1; //adds the end of the disk to the request array (0 if DOWN, disk-1 if UP)
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if( dir == 0)
            { //if the direction is DOWN, it will sort in descending order
                if(temp[j] < temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            else
            { //if the direction is UP, it will sort in ascending order
                if(temp[j] > temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            
        }
    }
    
    
    for(i=0;i<n;i++)
    {
        if(temp[i]==head)
        {
            pos=i; //finds the position of the head in the sorted request array
            break;
        }
    }
    head= temp[pos];
    for(i=pos+1;i<n;i++)
    { // it will go to the right of the head to lower if DOWN ( descending order) or toupper if UP (ascending order)
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]); //adds the seek time to the total seek time
        head=temp[i];
    }
    
    for(i=pos-1; i>=0;i--)
    { // it will go to the left of the head to lower if DOWN ( descending order) or toupper if UP (ascending order)
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]); //adds the seek time to the total seek time
        head=temp[i];
    }
    printf("\nSeek time for SCAN is: %d\n\n", seek);
}


void cscan(int head , int dir)
{
    int temp[max+3], pos, i,j, t, n=max, seek=0;
    for(i=0;i<n;i++)
    {
        temp[i]= requests[i];
    }
    temp[n++]=head; //adds the head to the request array
    temp[n++]=0;    //adds the beginning of the disk to the request array
    temp[n++]=disk-1; //adds the end of the disk to the request array
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if( dir == 0)
            { //if the direction is DOWN, it will sort in descending order
                if(temp[j] < temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            else
            { //if the direction is UP, it will sort in ascending order
                if(temp[j] > temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            
        }
    }
    
    
    for(i=0;i<n;i++)
    {
        if(temp[i]==head)
        {
            pos=i; //finds the position of the head in the sorted request array
            break;
        }
    }
    head= temp[pos];
    for(i=pos+1;i<n;i++)
    { // it will go to the right of the head to lower if DOWN ( descending order) or toupper if UP (ascending order)
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]); //adds the seek time to the total seek time
        head=temp[i];
    }
    
    for(i=0; i<=pos-1;i++)
    {// it will go from the start (either lowest or highest) towards the head
        printf("%d\t", temp[i]);
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]);
        head=temp[i];
    }
    printf("\nSeek time for CSCAN is: %d\n\n", seek);
}



void look(int head , int dir)
{
    int temp[max+1], pos=0, i,j,n=max, t, seek=0;
    for(i=0;i<max;i++)
    {
        temp[i]= requests[i];
    }
    temp[n++]=head; //adds the head to the request array
        
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if( dir == 0)
            {   //if the direction is DOWN, it will sort in descending order
                if(temp[j] < temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            else
            {   //if the direction is UP, it will sort in ascending order
                if(temp[j] > temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            
        }
    }
    
    
    for(i=0;i<n;i++)
    {
        if(temp[i]==head)
        {
            pos=i;
            break;
        }
    }
    
    head= temp[pos];
    
    for(i=pos+1;i<n;i++)
    {
        // it will go to the right of the head to lower if DOWN ( descending order) or toupper if UP (ascending order)
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]);
        head=temp[i];
    }
    
    for(i=pos-1; i>=0;i--)
    {   // it will go to the left of the head to lower if DOWN ( descending order) or toupper if UP (ascending order)
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]);
        head=temp[i];
    }
    printf("\nSeek time for LOOK is: %d\n\n", seek);
}


void clook(int head, int dir)
{
    int i, j, temp[max+1], n=max,t, pos=0, seek=0;
    for(i=0;i<n;i++)
        temp[i]= requests[i];
    
    temp[n++]= head; //adds the head to the request array
    
    for(i=0;i<n;i++)
    {
        for(j=0; j<n-1;j++)
        {
            if(dir == 0)
            { //if the direction is DOWN, it will sort in descending order
                if(temp[j] < temp[j+1] )
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
            else
            { //if the direction is UP, it will sort in ascending order
                if(temp[j] > temp[j+1])
                {
                    t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
        }
    }
    
    
    for(i=0;i<n;i++)
    {
        if(head== temp[i])
        {
            pos=i;
            break;
        }
    }
    
    head=temp[pos];
    
    for(i=pos+1;i<n;i++)
    { // it will go to the right of the head to lower if DOWN ( descending order) or toupper if UP (ascending order)
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]);
        head=temp[i];
    }
    for(i=0;i<=pos-1;i++)
    {  // it will go from the start (either lowest or highest) towards the head
        printf("%d\t", temp[i]);
        seek+= abs(head - temp[i]);
        head=temp[i];
    }
    printf("\nSeek time for LOOK is: %d\n\n", seek);
    
}



int main()
{    
    printf("\nEnter head value: ");
    scanf("%d", &head);
    
    
    fcfs(head);
    sstf(head);
    scan(head, 1);
    cscan(head, 1);
    look(head, 1);
    clook(head, 1);
    return 0;
}