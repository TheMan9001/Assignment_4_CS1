#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

//function merge is needed for the merge sort
void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    //create two arrays
    int L[n1], R[n2];
	
	//split the original array into the two arrays created above
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
	}
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
	}
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    //Copies any remaining numbers between the two arrays back into the original array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int pData[], int l, int r){
	if(l < r){
		int mid = (l+r)/2;
		
		mergeSort(pData, l, mid);
		mergeSort(pData, mid+1, r);
		
		merge(pData, l, mid, r);
	}
}


// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n){
	//j is called outside of its loop because j is used 
    //outside of the loop its made for
	int temp, j;
	for(int i = 1; i < n; i++){
	    temp = *(pData + i);
	    for(j = i-1; j >= 0; j--){
	        if(*(pData+j) > temp){
	            *(pData+(j+1)) = *(pData+j);
	        }else{
	           break; 
	        }
	    }
	    //this is the reason j is called at the top of the function
	    *(pData+(j+1)) = temp;
	    
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n){
	int temp;
    //this loop stops one before the last number in the array because
    //the function compares the current number with the next number in the array
    for (int i = 0; i < n-1; i++) {
        //(n-i)-1 is used to stop the function from rechecking numbers 
        //that are already sorted
        for (int j = 0; j < (n-i)-1; j++) {
            //if current number is greater than next number then swap numbers
            if (*(pData + j) > *(pData + (j+1))) { 
                temp = *(pData + (j+1)); 
                *(pData + (j+1)) = *(pData + j); 
                *(pData + j) = temp; 
            } 
        } 
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n){
	int temp, minIndex;
	for(int i = 0; i < n-1; i++){
		//finds the index of the lowest number
		minIndex = i;
		for(int j = (i+1); j < n; j++){
			if(*(pData+j) < *(pData+minIndex)){
				minIndex = j;
			}
		}
		//swaps the lowest number with the number at the lowest index(bottom of list)
		temp = *(pData+i); 
        *(pData+i) = *(pData+minIndex); 
        *(pData+minIndex) = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData){
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile){
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for(int i = 0; i < dataSz; i++){
			fscanf(inFile, "%d ", *(ppData+i));
			
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz){
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i){
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i){
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void){
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i){
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0){
			continue;
		}
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}