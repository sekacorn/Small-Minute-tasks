//Cornelius Sekamatte
include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Sums up the numbers 
void *SumUp(void* ptr)
{	

	int a = 0;
	int sum = 0;
	int num = *(int *)ptr;
	
	while(a <= num)
	{
		sum += a;
		a++;
	}

	printf("Sum of number %d is: %d\n",num,sum);
}

// finds factorial 
void *Factorial(void * ptr)
{
	int i,n = *(int *)ptr;
	int fact = 0;

	for( i = 0; i <= n; i++)
	{
		if(i == 0)
			fact = 1;
		else
			fact *= i;
	}

	printf("Factorial of number %d is: %d\n",n,fact);
}


int main(int argc, char * argv[])
{
	int i,n = atoi(argv[1]);
	pthread_t threads[2];
	int rc;

	for(i = 0; i < 2; i++)
	{
		if(i == 0)
		{
		    rc = pthread_create(&threads[0], NULL, SumUp, (void *)&n);
			
                        if(rc != 0)
			{
			    printf("ERROR ERROR windows 95");
			    exit(1);
			}
		}

		else
		{
		    rc = pthread_create(&threads[1], NULL, Factorial, (void *)&n);
                        
			if(rc != 0)
			{
			    printf("ERROR ERROR Windows 95");
			    exit(1);
			}
		}
	}

	pthread_exit(NULL);

	return 0;
}










