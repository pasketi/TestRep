#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

typedef int bool;
#define TRUE 1
#define FALSE 0
#define arrayLength 30000
#define maxValue arrayLength
#define BASE 10

void fillArray(int *array, int amount, int style);
void copyArray(int *arrayFrom, int *arrayTo, int amount);
void quickSort(int *array, int first, int last);
void swap(int *array, int a, int b);
void printArray(int *array, int amount);
void checkArray(int *array, int amount);
double calculateSpread(double *array, int amount, int table, double *avg);

int main()
{   
    int loop = 0, loopMax = 5;
    double values[5][loopMax], increment[5] = {0,0,0,0,0}, averages[5] = {0,0,0,0,0}, spreads[5] = {0,0,0,0,0};
    do{
        long startTime, endTime;
        unsigned int x = arrayLength;
        int arrayA[x], arrayB[x], arrayC[x], arrayD[x], arrayE[x];
        
        fillArray(arrayA, x, 1);
		fillArray(arrayB, x, 2);
		fillArray(arrayC, x, 3);
		fillArray(arrayD, x, 4);
		fillArray(arrayE, x, 5);
		
		/*
		printArray(arrayA, x);
        printf("\n\n");
        printArray(arrayB, x);
        printf("\n\n");
        printArray(arrayC, x);
        printf("\n\n");
        printArray(arrayD, x);
        printf("\n\n");
        printArray(arrayE, x);
        printf("\n\n");
        
        system("pause");
        */
        
        printf("Starting QuickSort: Random\n");
        startTime = GetTickCount();
        quickSort(arrayA, 0, x);
        endTime = GetTickCount();
        increment[0] += (double)(endTime-startTime)/1000;
        values[0][loop] = (double)(endTime-startTime)/1000;
        printf("Done! Took %.2f s\n\n", (double)(endTime-startTime)/1000);
        
        printf("Starting QuickSort: In order\n");
        startTime = GetTickCount();
        quickSort(arrayB, 0, x);
        endTime = GetTickCount();
        increment[1] += (double)(endTime-startTime)/1000;
        values[1][loop] = (double)(endTime-startTime)/1000;
        printf("Done! Took %.2f s\n\n", (double)(endTime-startTime)/1000);
        
        printf("Starting QuickSort: Reversed\n");
        startTime = GetTickCount();
        quickSort(arrayC, 0, x);
        endTime = GetTickCount();
        increment[2] += (double)(endTime-startTime)/1000;
        values[2][loop] = (double)(endTime-startTime)/1000;
        printf("Done! Took %.2f s\n\n", (double)(endTime-startTime)/1000);
        
        printf("Starting QuickSort: 1,100,2,99...\n");
        startTime = GetTickCount();
        quickSort(arrayD, 0, x);
        endTime = GetTickCount();
        increment[3] += (double)(endTime-startTime)/1000;
        values[3][loop] = (double)(endTime-startTime)/1000;
        printf("Done! Took %.2f s\n\n", (double)(endTime-startTime)/1000);
        
        printf("Starting QuickSort: 100,1,99,2\n");
        startTime = GetTickCount();
        quickSort(arrayE, 0, x);
        endTime = GetTickCount();
        increment[4] += (double)(endTime-startTime)/1000;
        values[4][loop] = (double)(endTime-startTime)/1000;
        printf("Done! Took %.2f s\n\n", (double)(endTime-startTime)/1000);
    
        printf("Checking arrays...\n\n");
        
        //prints
        printf("\n\nChecking QuickSort: Random\n");
        checkArray(arrayA, x);
        printf("\n\nChecking QuickSort: Sorted\n");
        checkArray(arrayB, x);
        printf("\n\nChecking QuickSort: Reversed\n\n");
        checkArray(arrayC, x);
        printf("\n\nChecking QuickSort: 1,100,2,99...\n");
        checkArray(arrayD, x);
        printf("\n\nChecking QuickSort: 100,1,99,2\n");
        checkArray(arrayE, x);

        printf("\n\n");
        loop++;
    }while(loop < loopMax);
    
    int i;
    for(i = 0; i < 5;i++){
          averages[i] = increment[i]/loopMax;
    }
    
    for(i = 0; i < 5;i++){
          spreads[i] = calculateSpread(values[i], loopMax, i, averages);
    }
    
    printf("Random \n");
    printf("Average: %.2f \n", averages[0]);
    printf("Spread: %.2lf \n\n", spreads[0]);
    printf("Sorted \n");
    printf("Average: %.2f \n", averages[1]);
    printf("Spread: %.2lf \n\n", spreads[1]);
    printf("Reversed \n");
    printf("Average: %.2f \n", averages[2]);
    printf("Spread: %.2lf \n\n", spreads[2]);
    printf("1,100,2,99... \n");
    printf("Average: %.2f \n", averages[3]);
    printf("Spread: %.2lf \n\n", spreads[3]);
    printf("100,1,99,2... \n");
    printf("Average: %.2f \n", averages[4]);
    printf("Spread: %.2lf \n\n", spreads[4]);
    
    system("PAUSE");
    return 0;
}

void fillArray(int *array, int amount, int style){
     int i = 0;
     srand(time(NULL)*time(NULL)-time(NULL));
	 if (style == 1){
		do{
			array[i] = rand() % maxValue;
			i++;
		}while(i < amount);
	 } else if (style == 2) {
		do {
			array[i] = i++;
		} while(i < amount);
	 } else if (style == 3) {
		do {
			array[i] = amount - i++;
		} while(i < amount);
	 } else if (style == 4) {
		do {
			array[i] = i++;
			array[i] = amount - i++;
		} while(i < amount);
	 } else if (style == 5) {
		do {
			array[i] = amount - i++;
			array[i] = i++;
		} while(i < amount);
	 }
	 i = 0;
}

void copyArray(int *arrayFrom, int *arrayTo, int amount){
     int i = 0;
     do{
         arrayTo[i] = arrayFrom[i];
         i++;
     }while(i<amount);
}

void quickSort(int *array, int first, int last){
     int pivot,j,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(array[i]<=array[pivot]&&i<last)
                 i++;
             while(array[j]>array[pivot])
                 j--;
             if(i<j){
                 swap(array, i, j);
             }
         }

         swap(array, pivot, j);
         quickSort(array,first,j-1);
         quickSort(array,j+1,last);

    }
}

void swap(int *array, int a, int b){
     int c = array[a];
     array[a] = array[b];
     array[b] = c;
}

void printArray(int *array, int amount){
     int i;
     for (i=0;i<amount;i++){
         printf("%i ", array[i]);
     }
}

void checkArray(int *array, int amount){
     bool correct = TRUE;
     int i;
     for (i=0;i<amount-1;i++){
         if (array[i] > array[i+1]){
            correct = FALSE;
         }
     }
     if (correct == FALSE){
        printf("Array NOT sorted\n");
        printArray(array, amount);
     }
     else{
          printf("Array is sorted\n");
     }
}

double calculateSpread(double *array, int amount, int table, double *avg){
     double xix;
     int i;
     for (i = 0; i < amount; i++){
         (double)xix += (double)pow(((double)array[i]-(double)avg[table]), 2);
     }
     return (double)sqrt(((double)1/((double)amount-(double)1))*(double)xix);
}
