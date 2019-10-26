#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <pthread.h> 

#define INTERVAL 10000		//decide number of intervals
#define THREADS 1000		//decide number of threads


/*global variables*/
long long  i;		
double x,y,dis,pi;
double cclPnts=0, sqPnts =0;
int high =1, low =0;
int count=0;

pthread_t tids[THREADS];	//create thread array

pthread_mutex_t lock;		//create mutex object


/*MonteCarlo Algorithm*/
void* monteAlgo(void *arg)
{
        for(i =0; i<(INTERVAL*INTERVAL);i++)
    {
       
	/*Generate random numbers*/
        x = ((double)rand() * (high - low )) / (double)RAND_MAX + low; 
        y = ((double)rand() * (high - low )) / (double)RAND_MAX + low;


        dis = x*x + y*y; 	//calculate distance 

        pthread_mutex_lock(&lock);
        if(dis <= 1)    /*check whether inside or not*/
            cclPnts++;
        

        sqPnts++;
        pthread_mutex_unlock(&lock);
        
        count++;

        
    }

}   

int main(int argc, char const *argv[])
{
	/*create threads*/
    for(int j=0; j<THREADS; j++)
    {
        pthread_create(&tids[j],NULL,monteAlgo,NULL);
    }


	/*calculate pi values*/
    for(int k=0; k<THREADS;k++)
    {

     if(count >0)
     {  
         pthread_mutex_lock(&lock);
         pi = (4 * cclPnts) / sqPnts;
         pthread_mutex_unlock(&lock);
         printf("\nFinal Estimation of Pi = %lf\n ", pi);
     }   
    }

   // printf("Number of Points Inside the ccl: %2lf   Total Points : %2lf\n",sqPnts,cclPnts);
    return 0;
}
