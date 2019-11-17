#include<stdio.h> 
#include<omp.h>
#include <stdlib.h>
#include<time.h>

// A utility function to swap two elements 

void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 
 


/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */

int partition(int arr[], int low, int high) 
{ 
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element 

	for (int j = low; j <= high - 1; j++) { 

		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] <= pivot) { 

			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

// Generates middle Pivot, swaps pivot with 
// end element and calls the partition function 
int partition_r(int arr[], int low, int high) 
{ 
	
	// low .. high 
	srand(time(NULL)); 
	int random = low + (high/2) % (high - low); 

	// Swap A[random] with A[high] 
	swap(&arr[random], &arr[high]); 

	return partition(arr, low, high); 
} 

/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
	if (low < high) { 

		/* pi is partitioning index, arr[p] is now 
		at right place */
		int pi = partition_r(arr, low, high); 

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
} 

//function to merge two subsequence 
void merge(int *arr,int id,int size)
{	int a[2][size];
	int x=2*id*size;
	for (size_t i = 0; i < 2*size; i++)
	{	if (i<size)
			a[0][i%size]=arr[x];
		else
			a[1][i%size]=arr[x];
			x++;	
	}
	x=2*id*size;
	int i=0,j=0;
	while(i<size&&j<size)
	{
		if (a[0][i]<a[1][j])
		{
			arr[x]=a[0][i];i++;	
		}
		else
		{
			arr[x]=a[1][j];j++;
		}
		x++;	
	}
	while(i<size)
	{
		arr[x]=a[0][i];
		i++;x++;
	}
	while(j<size)
	{
		arr[x]=a[1][j];
		j++;x++;
	}
}


//function to copy integer type arry
void cp_array(int *a,int *b,int size)
{
	//int size=sizeof(a)/sizeof(a[0]);
	for (size_t i = 0; i <size; i++)
		b[i]=a[i];
}


int main() 
{   
	
	int n=262144,x=n;
	int arr[n]; 
	int temp[n];
	printf("Enter case no ---------\n1:worst case\n2:average case\n3:best case\n4:exit\n");
	int select;
	scanf("%d",&select);

	//srand(time(NULL));
    
	FILE *fp=NULL;
	switch(select)
	{
	case 1:
			fp=fopen("worst.text","w");
			for (size_t i = 0; i < n; i++)
				{
        			arr[i]=x;x--;
    			} 

			break;
	case 2:
			fp=fopen("average.text","w");
		
			for (size_t i = 0; i < n; i++)
				{   if(i==n/2)
        			   arr[i]=i+1;
					else
					{
						arr[i]=x+10;x--;
					}
				
    			} 
			break;
	case 3:
			fp=fopen("best.text","w");
			for (size_t i = 0; i < n; i++)
				arr[i]=i;	
			break;
	case 4:
			exit(0);
			break;
	default:
			exit(0);
			break;
	}

	cp_array(arr,temp,n);
	int z=2,max_num_pro=100;   //z <= mininum no of processor
for (z = 2; z <max_num_pro; z=z*2)
{
	double avg_exe=0.0;
	int avi=20;
for(int av=0;av<avi;av++)   //  loop to calculate average execution time
{
    int pro=z;
    int seq_size=n/pro;
	double a=omp_get_wtime();
	omp_set_num_threads(pro);     //  creating threads
    
	// ----------------------------------------------------------------
	//parallel quicksort of subsequence
	//----------------------------------------------------------------
    #pragma omp parallel      
    {
        
        int id=omp_get_thread_num();
        quickSort(arr, id*seq_size, id*seq_size+seq_size-1);
       
         
    }

    //------------------------------------------


	for (size_t i = pro/2; i >=1; i=i/2)
	{
		 omp_set_num_threads(i);   //  creating threads
		/*------------------------------
	          parallel merging of subsequence using sequential merge algorithm
		  ----------------------------*/
		
    	#pragma omp parallel      
		{
			int id=omp_get_thread_num();
			merge(arr,id,seq_size);
//uncomment to print merge sequence
// 			for (size_t j = 0; j < n; j++)
//             {
//                 printf("%d ",arr[j]);
//             }
        	
//            printf("\n");
        
        }
		seq_size=seq_size*2;
		
	}
	 
	printf("Array sorted ------------ of size :%d----------by %d processors-------\n",n,z); 
	
			//uncomment to print sorted sequence
            // for (size_t i = 0; i < n; i++)
            // {
            //     printf("%d ",arr[i]);
            // }
            
    double b=omp_get_wtime();
	avg_exe=avg_exe+b-a;
	cp_array(temp,arr,n);
	}
	avg_exe=avg_exe/(double)avi;
	printf("average execution time :\n\n%f\n\n",avg_exe);
	fprintf(fp,"%d %f\n",z,avg_exe);
	}
	fclose(fp);

	return 0; 
} 
