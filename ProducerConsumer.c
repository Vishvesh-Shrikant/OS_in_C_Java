#include <stdio.h>
#include <stdlib.h>

int mutex=1; //mutex to lock or unlock the process
int empty=10; // empty slots in the buffer
int full=0; // full slots in the buffer
int x=0; // to show the item no. being produced/consumed

void produce()
{
    if(mutex==1 && empty!=0)
    {
        --mutex; // lock the process
        --empty; // decrease empty slots
        ++full; // increase full slots
        printf("\nProduced item no. %d\n", ++x);
        ++mutex; // unlock the process
    }
    else 
        printf("\nBuffer is full.\n");
}

void consume()
{
    if(mutex==1 && full!=0)
    {
        --mutex; // lock the process
        ++empty;    // increase empty slots
        --full;   // decrease full slots
        printf("Consumed item no. %d\n", x--);
        ++mutex;    // unlock the process
    }
    else
        printf("\nBuffer is empty.\n");
}
int main()
{
    int running=1, choice;
    do
    {
        printf("\n1. Produce item\n2. Consume item\n3. Terminate process");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                produce();
                break;
            case 2:
                consume();
                break;
            case 3:
                running=0;
                break;
            default:
                printf("\nENTER VALID INPUT\n");
        }
    }while (running !=0 );
    
    return 0;
}



