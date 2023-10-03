#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randarr(int arr[], int length, int max){
    
    int i, j;
    for(i=0;i<length;i++){
        arr[i]=rand()%max;
	}
	printf("\nElements of the array:\n");
    for(j=0;j<length;j++)
    {
        printf("%d ", arr[j]);
    }
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void printArray(int arr[], int n)
{
	int i;
    printf("\nElements of the array sorted:\n");
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	srand(time(NULL));
    
	int length, i, j, max, t_start, t_end, t_elapsed, t_tot=0;
    
	printf("\nEnter the size of array: "); /*goes from 0 to 2094329*/
    scanf("%d", &length);
    
	int randArray[length];
	
	printf("Enter the max so as the random generator goes from 0 to max: ");
	scanf("%d", &max);
    
    randarr(randArray, length, max);

    int n = sizeof(randArray) / sizeof(randArray[0]);

	t_start = clock();
	insertionSort(randArray, n);
	t_end = clock();
	t_elapsed = t_end - t_start;
	t_tot = t_tot + t_elapsed;
	printf("\n\nTime needed to sort %d elements: %d clock cycles", length, t_tot);

    printf("\n");

    printArray(randArray, n);
    
    printf("\n");

    return 0;
}
