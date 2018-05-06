#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#define random(x) (rand()%x)
#define bufferSize 5

DWORD WINAPI Producer(LPVOID);
DWORD WINAPI Consumer(LPVOID);

int produce_item(int item);
int consume_item(int *item);

HANDLE Mutex;
HANDLE Full, Empty;

int product[bufferSize-1];

int i,j;
int ip=0,ic=0,ipN,icN;

int randNum;

int buffer=0;

int main()
{
    printf("The number of Producer: ");
    scanf("%d",&ipN);
    printf("The number of Consumer: ");
    scanf("%d",&icN);
    printf("\n\n");

    Mutex = CreateMutex(NULL,FALSE,NULL);
    Full  = CreateSemaphore(NULL,0,bufferSize,NULL);
    Empty = CreateSemaphore(NULL,bufferSize,bufferSize,NULL);

    HANDLE p[ipN-1],c[icN-1];

    for(ip=0;ip<=ipN-1;ip++){
        p[ip] = CreateThread(NULL,0,Producer,NULL,0,NULL);
        printf("\n PRODUCER%d created",ip+1);

        if (p[ip]==NULL) return -1;
    }

    for(ic=0;ic<=icN-1;ic++){
        c[ic] = CreateThread(NULL,0,Consumer,NULL,0,NULL);
        printf("\n CONSUMER%d created",ic+1);

        if (c[ic]==NULL) return -1;
    }

    getch();
    return 0;
}

DWORD WINAPI Producer(LPVOID lpPara)
{
    while(TRUE){

        WaitForSingleObject(Empty,INFINITE);
        WaitForSingleObject(Mutex,INFINITE);

        srand(time(NULL)+i);
        randNum=random(1000);
        int Presult;
        Presult=produce_item(randNum);

        if(Presult==1)
        {
            printf("\n Producer produced %d \t buffer now: %d/5 \n\n",randNum,buffer);
            if(buffer>=bufferSize) printf("\n buffer is full,please wait\n\n");
            ReleaseMutex(Mutex);
            ReleaseSemaphore(Full,1,NULL);
        }

        else if(Presult==0)
        {
            printf("produce failed\n");
            ReleaseMutex(Mutex);
        }

        i++;

        Sleep(1000);
    }

    return 0;
}


DWORD WINAPI Consumer(LPVOID lpPara)
{
    while(TRUE){


        WaitForSingleObject(Full,INFINITE);
        WaitForSingleObject(Mutex,INFINITE);

        int num;
        int result=consume_item(&num);

        if(result>0)
        {
            printf("Consumer consumed %d \t buffer now: %d/5 \n\n",product[buffer],buffer);
            product[buffer]=0;
            if(buffer==0) printf("\n buffer is empty,please wait\n\n");

            ReleaseMutex(Mutex);
            ReleaseSemaphore(Empty,1,NULL);
            Sleep(1000);
        }

        else
        {
            printf("\n comsume failed \n");
            ReleaseMutex(Mutex);
        }
    }
    return 0;
}

int produce_item(int item)
{

    if(0 < buffer <= bufferSize)
    {
        product[buffer] = item;
        buffer++;
        return 1;
    }

    else return 0;
}

int consume_item(int *item)
{
    if(0 < buffer <= bufferSize)
    {
        item= &product[buffer];
        product[buffer]=0;
        buffer--;
        return *item;
    }
    else return 0;
}
