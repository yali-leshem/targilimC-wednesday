/*------------------------------------------------------
* Filename: dynamic_struct_YaliLeshem.c
* Description: define and use a dynamic struct representing time
* Author: Yali Leshem
-------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define HOURS 24
#define MINS 60
#define SECS 60
#define SUCCESS 0
#define FAILURE 1

typedef struct { // struct representing time by seconds, minutes and hours
    int seconds;
    int minutes;
    int hours;
} Time;

/*------------------------------------------------------
* Function Name - sum_times
*
* Function Purpose - Recieve two time structs and sum them accordingly and print and return the summed time struct
*
* Parameters – two time structs as defined above - first_time and second_time
*
* Return value - NULL in case there was a failure, otherwise the Time struct 'summed_time' representing the sum of first_time and second_time
*
-------------------------------------------------------*/

Time* sum_times(Time *first_time, Time *second_time) {
    int sec3, min3, hrs3;
    Time* summed_time = (Time*) malloc(sizeof(Time));

    if (summed_time == NULL) { // In case dynamic memory allocation failed
        printf("Error has occured during memory allocation. exiting program \n");
        return NULL;
    }

    sec3 = first_time->seconds + second_time->seconds;
    min3 = first_time->minutes + second_time->minutes;
    hrs3 = first_time->hours + second_time->hours;
    
    // When passed a minute, hour or an entire day, updated variables
    if (sec3 >= SECS) {
        sec3 -= SECS;
        min3++; // In case a minute passed
    }

    if (min3 >= MINS) {
        min3 -= MINS;
        hrs3++; //In case an hour passed
    }

    if (hrs3 >= HOURS)
        hrs3 -= HOURS; // In case a day has passed

    // Assign sumed times to sum_result Time object.
    summed_time->seconds = sec3;
    summed_time->minutes = min3;
    summed_time->hours = hrs3;

    // print the summed object in time format
    printf("Summed time: %02d:%02d:%02d \n", summed_time->hours, summed_time->minutes, summed_time->seconds);

    return summed_time;
}

// main returns 0 for success, 1 for failure
int main() {
    int sec1, sec2, min1, min2, hrs1, hrs2;

    // Recieve input for the first time
    printf("Enter first seconds: \n");
    scanf("%d", &sec1);
    printf("Enter first minutes: \n");
    scanf("%d", &min1);
    printf("Enter first hours: \n");
    scanf("%d", &hrs1);

    // Recieve input for the second time
    printf("Enter second seconds: \n");
    scanf("%d", &sec2);
    printf("Enter second minutes: \n");
    scanf("%d", &min2);
    printf("Enter second hours: \n");
    scanf("%d", &hrs2);

    // In case one of the numbers recieved as an input are invalid
    if (sec1 < 0 || sec1 >= SECS || min1 < 0 || min1 >= MINS || hrs1 < 0 || hrs1 >= HOURS
        || sec2 < 0 || sec2 >= SECS || min2 < 0 || min2 >= MINS || hrs2 < 0 || hrs2 >= HOURS) {
        printf("Invalid input! Seconds/minutes must be between 0-59, hours 0-23 \n");
        return FAILURE;
    }

    Time* first_time = (Time *) malloc(sizeof(Time));
    Time* second_time = (Time *) malloc(sizeof(Time));
    Time* summed_time;

    if (first_time == NULL || second_time == NULL) { // if memory allocation failed
        printf("Error has occured during memory allocation. exiting program");
        return FAILURE;
    }

    // Assign both Time struct objects to the input from user
    first_time->seconds = sec1;
    first_time->minutes = min1;
    first_time->hours = hrs1;

    second_time->seconds = sec2;
    second_time->minutes = min2;
    second_time->hours = hrs2;

    // print both times in time fitting format using '%02d' to have zero from the left in case a single digit
    printf("First time:  %02d:%02d:%02d \n", first_time->hours, first_time->minutes, first_time->seconds);
    printf("Second time: %02d:%02d:%02d \n", second_time->hours, second_time->minutes, second_time->seconds);

    summed_time = sum_times(first_time, second_time); // sum both times

    // free dynamic memory allocation
    free(summed_time);
    free(second_time);
    free(first_time);

    return SUCCESS;
}