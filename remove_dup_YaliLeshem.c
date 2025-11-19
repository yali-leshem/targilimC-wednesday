/*------------------------------------------------------
* Filename: remove_dup_YaliLeshem.c
* Description: 3 functions to use on sorted arrays in order to remove duplicates within them, using dynamic memory
* Author: Yali Leshem
-------------------------------------------------------*/
#include <Stdio.h>
#include <stdlib.h>

#define MAX_LEN 128
#define SUCCESS 0
#define FAILURE 1

void print_arr (int *arr, int count) { // Recieve int pointer and length of array and print all of its elements
    int index;
    for (index = 0; index < count; index++)
        printf(" %d", *(arr+index));
    printf("\n");
}

/*------------------------------------------------------
* Function Name - removeDup_ver1
*
* Function Purpose - return the new sorted dynamic array with non-duplicates only, and pass its size
*e
* Parameters – int *size - for passing its size, int sorted_arr[] - the original sorted array
*
* Return value - Null for failure, and the address to the new sorted dynamic array is succeed
*
-------------------------------------------------------*/

int * removeDup_ver1 (int *size, int sorted_arr[]) {
    int count = 1, len = *(size); // Store the full length of sorted array
    int *index = sorted_arr, *new_sorted;

    // first initialize new dynamic array using malloc
    new_sorted = (int*) malloc(sizeof(int));
    if (new_sorted == NULL) {
        printf("dynamic memory allocation failed \n");
        return NULL;
    }
    *(new_sorted) = *(index);

    index = sorted_arr + 1;
    while (index != &sorted_arr[len]) { // iterate from second element up to one-past-last
        if (*(new_sorted + count - 1) != *(index)) { 
            new_sorted = (int*) realloc(new_sorted, (count+1) * sizeof(int));

            if (new_sorted == NULL) { // if dynamic memory failed
                printf("dynamic memory allocation failed \n");
                return NULL;
            }

            *(new_sorted + count) = *(index); // store next non-duplicate element
            count++;
        }
        index++; // move pointer by 1 to the next element in array
    }
    *(size) = count;
    return new_sorted; 
}

/*------------------------------------------------------
* Function Name - removeDup_ver2
*
* Function Purpose - Passing values for the new dynamic array, and return its size
*
* Parameters – int **new_arr - for the new dynamic array, int *size - for passing its size, int sorted_arr[] - the original sorted array
*
* Return value - 1 for failure, otherwise the number of elements in the new sorted dynamic array
*
-------------------------------------------------------*/

int removeDup_ver2 (int **new_arr, int size, int sorted_arr[]) {
    int count = 1, len = size; // store the length of sorted array
    int *index = sorted_arr, *new_sorted; // using two-pointers method for ensuring there are no duplicates in array

    // first initialize new dynamic array using malloc
    new_sorted = (int*) malloc(sizeof(int));
    if (new_sorted == NULL) {
        printf("dynamic memory allocation failed \n");
        return FAILURE;
    }
    *(new_sorted) = *(index);

    index = sorted_arr + 1;
    while (index != &sorted_arr[len]) { // iterate from second element up to one-past-last
        if (*(new_sorted + count - 1) != *(index)) { 
            new_sorted = (int*) realloc(new_sorted, (count+1) * sizeof(int));

            if (new_sorted == NULL) {
                printf("dynamic memory allocation failed \n");
                return FAILURE;
            }

            *(new_sorted + count) = *(index); // store next non-duplicate element
            count++;
        }
        index++; // move pointer by 1 to the next element in array
    }
    *(new_arr) = new_sorted;
    return count; 
}

/*------------------------------------------------------
* Function Name - removeDup_ver3
*
* Function Purpose - Passing values for the new dynamic array, and its size
*
* Parameters – int **new_arr - for the new dynamic array, int *size - for passing its size, int sorted_arr[] - the original sorted array
*
* Return value - 0 if Success, and 1 for Failure
*
-------------------------------------------------------*/

int removeDup_ver3 (int **new_arr, int *size, int sorted_arr[]) {
    int count = 1;
    int *index, *new_sorted;
    int len = *(size);

    // first initialize new dynamic array using malloc
    new_sorted = (int*) malloc(sizeof(int));
    if (new_sorted == NULL) {
        printf("dynamic memory allocation failed \n");
        return FAILURE;
    }
    *(new_sorted) = *(sorted_arr);

    index = sorted_arr + 1;
    while (index != &sorted_arr[len]) { // iterate from second element
        if (*(new_sorted + count - 1) != *(index)) {
            new_sorted = (int*) realloc(new_sorted, (count+1) * sizeof(int));

            if (new_sorted == NULL) { // if dynamic memory failed
                printf("dynamic memory allocation failed \n");
                return FAILURE;
            }

            *(new_sorted + count) = *(index); // store next non-duplicate element
            count++;
        }
        index++; // move pointer by 1 to the next element in array
    }
    *(new_arr) = new_sorted;
    *(size) = count;
    return SUCCESS;
}

// Pointing out that success here is zero and failure is 1
int main () {
    int count, prev_num = 0, inc = 0, dec = 0, index = 0, sorted_arr[MAX_LEN];
    int *new_sorted;

    printf("Insert integers (up to %d) in sorted order \n", MAX_LEN);
    while (scanf(" %d",&sorted_arr[index]) == 1 || index == MAX_LEN) { // As long as integers are inserted
        if (prev_num < sorted_arr[index])
            inc = 1; // In case there's an increase
        else if (prev_num > sorted_arr[index])
            dec = 1; // In case found a decrease
        prev_num = sorted_arr[index];
        index++;
    }

    // If there was both an increase and a decrease - not sorted, return failure and exit. Do the same if only 1 element inserted
    if (inc && dec || index < 2) {
        printf("bad input. exiting program \n");
        return FAILURE;
    }

    count = index;
    new_sorted = sorted_arr;

    printf("Before sorting: \n");
    print_arr(new_sorted, count);

    new_sorted = removeDup_ver1(&count, sorted_arr);

    if (new_sorted == NULL)
        return FAILURE;

    printf("After sorting with removeDup 1st version: \n");
    print_arr(new_sorted, count);

    count = removeDup_ver2(&new_sorted, count, new_sorted);

    if (count == FAILURE)
        return FAILURE;
    
    printf("After sorting with removeDup 2nd version: \n");
    print_arr(new_sorted, count);

    if (removeDup_ver3(&new_sorted, &count, new_sorted))
        return FAILURE;

    printf("After sorting with removeDup 3rd version: \n");
    print_arr(new_sorted, count);

    free(new_sorted); // freeing the dynamic memory allocation used in functions
    return SUCCESS;
}