//get Average and Max and Min using pthreads
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define THREADS 4
#define MAX 20




int scores[MAX];
int count = 0;


// gets average and medium
void * Average()

{	float avg, medium;
	int i, mid, sum = 0,;
	

			  for( i = 0; i < count; i++)
				  sum += scores[i];

			  avg = (float)sum / count;

			  if(count % 2 == 1)
			  {
			    mid = (0+count)/2;
			    medium = scores[mid];
			  }

			  if(count % 2 == 0)
			  {
			    int x = (count / 2) - 1;
			    int y = (count / 2);
			    int n = scores[x] + scores[y];
			    mid = (float) n / 2;
			    medium = mid;
			  }

	  
			  printf("Medium : %.2f\n", medium);
			  printf("Average: %.2f\n", avg);
}

// Gets scores 
void * getTest()
{
			  int n, i;
			  printf("Enter 20 scores (-1 to exit): ");
			  for( i = 0; i < MAX; i++)
			  {
				  scanf("%d",&n);
				  if(n != -1)
				  {
					  scores[i] = n;
					  count++;
				  }
				  else
					  break;
			  }
}
// Gets minumum and maximum scores the user entered 
void * MinMax(void * ptr)
{
	int min = 0, max = 0;
	SortArr();
	min = scores[0];
	max = scores[count-1];

	printf("Minimum: %d\n", min);
	printf("Maximum : %d\n", max);

}

// Clears buffer
void * Clear1()
{
	fflush(stdout);
	memset(scores, 0, sizeof(scores));

	printf("Clearing\n");

	
}

// Sorts Array
void SortArr()
{
	int i, j;
	for(i = 0; i < count-1; i++)
		for(j = 0; j < count-i-1; j++)
			if(scores[j] > scores[j+1])
                        {
                           swap(&scores[j],&scores[j+1]);
                        }
}

// used in SortArr
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


int main()
{
	pthread_t th1, th2, th3, th4;
	SortArr();
	pthread_create(&th1, NULL, getTest, NULL);
	pthread_join(th1,NULL);
	pthread_create(&th2, NULL, Average, NULL);
	pthread_create(&th3, NULL, MinMax, NULL);
	pthread_join(th3, NULL);
	pthread_join(th2, NULL);
	pthread_create(&th4, NULL, Clear1, NULL);
	pthread_join(th4,NULL);

	return 0;
}








